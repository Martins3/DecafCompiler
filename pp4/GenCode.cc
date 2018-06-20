#include <iostream>
#include <vector>
#include <algorithm>
#include "./GenCode.hpp"
using namespace std;

GenCode * GenCode::G = new GenCode();

// 需要共享的四个变量， 用于检查类型
Type * GenCode::exprType = NULL;
deque<Hashtable<VarDecl *> * > * GenCode::nameScope = new deque<Hashtable<VarDecl*> *>(); // 获取局部变量　成员变量　和　全局变量的VarDecl
Hashtable<Decl *> * GenCode::globalDecl = new Hashtable<Decl *>();
ClassDecl * GenCode::curClass = NULL; // 方便this的访问


GenCode::GenCode(){
    codeGenerator = new CodeGenerator();
    gBreakLabels = new stack<const char *>();
}

Decl * GenCode::getGlobalDecl(const char * name){
    return globalDecl->Lookup(name);
}

FnDecl * GenCode::getMemberFn(ClassDecl * c, const char * name){
    for (int i = 0, n = c->members->NumElements(); i < n; ++i){
        Decl * d = c->members->Nth(i);
        FnDecl * v = dynamic_cast<FnDecl *>(d);
        if(v == NULL) continue;
        if(strcmp(name, v->id->name) == 0) return v;
    }
    return NULL;
}

bool GenCode::isSysCall(Call * c){
    // 只有 length()的调用　不是系统调用，其他的都是
    if(c->base == NULL) return false;
    c->base->handle(GetType::T);
    ArrayType * a = dynamic_cast<ArrayType *>(exprType);
    if(a != NULL && strcmp(c->field->name, "length") == 0){
        return true;
    }
    return false;
}

FnDecl * GenCode::getFnDeclByCall(Call * c){
    FnDecl * f = NULL;
    if(c->base == NULL){
        // 如果在Class 中间
        if(curClass != NULL){
            ClassDecl * classDecl = dynamic_cast<ClassDecl*>(getGlobalDecl(curClass->id->name));
            f = getMemberFn(classDecl, c->field->name);
        }

        // 搜索全局函数
        if(f == NULL){
            f = dynamic_cast<FnDecl*>(getGlobalDecl(c->field->name));
        }
        Assert(f != NULL);
    }else{
        c->base->handle(GetType::T);
        NamedType * n = dynamic_cast<NamedType *>(exprType);
        ClassDecl * classDecl = dynamic_cast<ClassDecl*>(getGlobalDecl(n->id->name));
        f = getMemberFn(classDecl, c->field->name);
    }
    return f;
}

VarDecl * GenCode::getMemberVar(ClassDecl * c, const char * name){
    for (int i = 0, n = c->members->NumElements(); i < n; ++i){
        Decl * d = c->members->Nth(i);
        VarDecl * v = dynamic_cast<VarDecl *>(d);
        if(v == NULL) continue;
        if(strcmp(name, v->id->name) == 0) return v;
    }
    return NULL;
}


// 只收集全局变量 和 局部变量，但是class 中间的变量不会收集
// 由于成员变量是通过偏移量来获取 堆栈的某一个位置
Location * GenCode::getMemLoc(const char * name){
    Location * l;
    for(auto t = scope.rbegin(); t != scope.rend(); t ++){
        l = (*t)->Lookup(name);
        if(l != NULL) return l;
    }
    return NULL;
}


VarDecl * GenCode::getNameVar(const char * name){
    VarDecl * l;
    for(auto t = nameScope->rbegin(); t != nameScope->rend(); t ++){
        l = (*t)->Lookup(name);
        if(l != NULL) return l;
    }
    return NULL;
}


void GenCode::handleProgram(Program * p){
    int offset = CodeGenerator::OffsetToFirstGlobal;
    auto var = new Hashtable<Location *>();
    scope.push_back(var);
    auto nameVar = new Hashtable<VarDecl *>();
    nameScope->push_back(nameVar);

    for (int i = 0, n = p->decls->NumElements(); i < n; ++i) {
        VarDecl *d = dynamic_cast<VarDecl*>(p->decls->Nth(i));
        if (d == NULL){
            globalDecl->Enter(p->decls->Nth(i)->id->name, p->decls->Nth(i));
            continue;
        }
        Location *loc = new Location(gpRelative, offset, d->id->name);
        var->Enter(d->id->name, loc);
        offset += CodeGenerator::VarSize;


        if(!BuildSymbol::B->isBaseType(d->type))
            nameVar->Enter(d->id->name, d);
    }

    // 预处理class 和 Interface确定其中的变量和函数的位置
    // 当前模式难以实现Interface
    for (int i = 0, n = p->decls->NumElements(); i < n; ++i) {
        ClassDecl *d = dynamic_cast<ClassDecl*>(p->decls->Nth(i));
        if(d == NULL) continue;
        if(d->vtable == NULL)
            handleClassMember(d);
    }

    for (int i = 0, n = p->decls->NumElements(); i < n; ++i){
        p->decls->Nth(i)->handle(GenCode::G);
    }

    codeGenerator->DoFinalCodeGen();
    scope.pop_back();
    nameScope->pop_back();
}

void GenCode::handleStmt(Stmt * s){
    printf("I can't be called !\n");
}

void GenCode::handleStmtBlock(StmtBlock * s){
    auto var = new Hashtable<Location *>();
    scope.push_back(var);
    auto nameVar = new Hashtable<VarDecl *>();
    nameScope->push_back(nameVar);

    for (int i = 0, n = s->decls->NumElements(); i < n; ++i) {
        VarDecl *d = dynamic_cast<VarDecl*>(s->decls->Nth(i));
        if (d == NULL) continue;
        Location * loc = codeGenerator->GenLocalVar(d->id->name, CodeGenerator::VarSize);
        var->Enter(d->id->name, loc);

        if(!BuildSymbol::B->isBaseType(d->type))
            nameVar->Enter(d->id->name, d);
    }

    for (int i = 0, n = s->stmts->NumElements(); i < n; ++i)
        s->stmts->Nth(i)->handle(GenCode::G);

    scope.pop_back();
    nameScope->pop_back();
}

void GenCode::handleConditionalStmt(ConditionalStmt * c){
    printf("I can't be called !\n");
}
void GenCode::handleLoopStmt(LoopStmt * l){
    printf("I can't be called !\n");
}

void GenCode::handleForStmt(ForStmt * f){
    const char* top = codeGenerator->NewLabel();
    const char* bot = codeGenerator->NewLabel();

    gBreakLabels->push(bot);

    f->init->handle(GenCode::G);
    codeGenerator->GenLabel(top);
    f->test->handle(GenCode::G);
    Location *t = returnLoc;
    codeGenerator->GenIfZ(t, bot);
    f->body->handle(GenCode::G);
    f->step->handle(GenCode::G);
    codeGenerator->GenGoto(top);
    codeGenerator->GenLabel(bot);

    gBreakLabels->pop();
}

void GenCode::handleWhileStmt(WhileStmt * w){
    const char* top = codeGenerator->NewLabel();
    const char* bot = codeGenerator->NewLabel();

    gBreakLabels->push(bot);

    codeGenerator->GenLabel(top);
    // 很有可能没有对应的返回值， 而且返回值是以前的
    w->test->handle(GenCode::G);
    Location *t = returnLoc;

    codeGenerator->GenIfZ(t, bot);
    w->body->handle(GenCode::G);
    codeGenerator->GenGoto(top);
    codeGenerator->GenLabel(bot);

    gBreakLabels->pop();

}
void GenCode::handleIfStmt(IfStmt * i){
    const char* els = codeGenerator->NewLabel();
    const char* bot = codeGenerator->NewLabel();

    i->test->handle(GenCode::G);
    Location *t = returnLoc;

    codeGenerator->GenIfZ(t, els);
    i->body->handle(GenCode::G);

    codeGenerator->GenGoto(bot);
    codeGenerator->GenLabel(els);
    if (i->elseBody) i->elseBody->handle(GenCode::G);
    codeGenerator->GenLabel(bot);
}

void GenCode::handleBreakStmt(BreakStmt * b){
    codeGenerator->GenGoto(gBreakLabels->top());
}

void GenCode::handleReturnStmt(ReturnStmt * r){
    if (r->expr == NULL){
        codeGenerator->GenReturn();
    } else{
        r->expr->handle(GenCode::G);
        codeGenerator->GenReturn(returnLoc);
    }
}
void GenCode::handlePrintStmt(PrintStmt * p){
    for (int i = 0, n = p->args->NumElements(); i < n; ++i) {
        Expr *e = p->args->Nth(i);
        e->handle(GetType::T);
        BuiltIn b;
        if(exprType == Type::boolType){
            b = PrintBool;
        }else if(exprType == Type::intType){
            b = PrintInt;
        }else if(exprType == Type::stringType){
            b = PrintString;
        }else{
            b = PrintInt; // 其他答应对应的地址
        }

        e->handle(GenCode::G);
        codeGenerator->GenBuiltInCall(b, returnLoc);
    }
}

/**
 * 对于所有声明只是一个指针
 * 当分析到VarDecl的时候停止
 * 导致之后都没有分析
 * 类型的作用是什么尚且不清楚
 *
 */
void GenCode::handleType(Type * t){
    printf("I am Type, I can't be accessed\n");
}

void GenCode::handleNamedType(NamedType * n){

}
void GenCode::handleArrayType(ArrayType * a){

}
void GenCode::handleNode(Node * n){
    printf("I am Node, I can't be accessed\n");
}
void GenCode::handleIdentifier(Identifier * i){
    printf("I am Identifier\n");
}
void GenCode::handleError(Error * e){
    printf("I am Error\n");
}
void GenCode::handleExpr(Expr * e){
    printf("I am Expr\n");
}
void GenCode::handleEmptyExpr(EmptyExpr * e){
    returnLoc = NULL;
}



void GenCode::handleIntConstant(IntConstant * i){
    // 需要向上返回位置，但是不知道变量的名称是什么
    returnLoc = codeGenerator->GenLoadConstant(i->value);
}

void GenCode::handleDoubleConstant(DoubleConstant * d){
    printf("I am DoubleConstant, double it's not supported !\n");
}

void GenCode::handleBoolConstant(BoolConstant * b){
    returnLoc = codeGenerator->GenLoadConstant(b->value);
}

void GenCode::handleStringConstant(StringConstant * s){
    // 目前不知道 这是如何处理的
    returnLoc = codeGenerator->GenLoadConstant(s->value);
}

void GenCode::handleNullConstant(NullConstant * n){
    // 暂时不是非常确地发生了什么！
    returnLoc = codeGenerator->GenLoadConstant(0);
}

void GenCode::handleOperator(Operator * o){
    printf("I am Operator, I can't be accessed !\n");
}

void GenCode::handleCompoundExpr(CompoundExpr * c){
    printf("I can't be accessed\n");
}

void GenCode::handleCalculateExpr(CompoundExpr * a){
    Location * l;
    if(a->left != NULL){
        a->left->handle(GenCode::G);
        l = returnLoc;
    }else{
         l = codeGenerator->GenLoadConstant(0);
    }

    a->right->handle(GenCode::G);
    Location * r = returnLoc;
    returnLoc = codeGenerator->GenBinaryOp(a->op->tokenString, l, r);
}


void GenCode::handleArithmeticExpr(ArithmeticExpr * a){
    handleCalculateExpr(a);
}

void GenCode::handleRelationalExpr(RelationalExpr * a){
    handleCalculateExpr(a);
}

void GenCode::handleEqualityExpr(EqualityExpr * a){
    handleCalculateExpr(a);
}

void GenCode::handleLogicalExpr(LogicalExpr * a){
    handleCalculateExpr(a);
}

void GenCode::handleAssignExpr(AssignExpr * a){
    a->right->handle(GenCode::G);
    Location *rtemp = returnLoc;

    LValue *lval = dynamic_cast<LValue*>(a->left);
    if (lval != NULL){
        storeLValue = true;
        assignLocPara = rtemp;
        lval->handle(GenCode::G);
        storeLValue = false;
        return;
    }

    // 都是表达式, 那么也对于左面加以分析
    a->left->handle(GenCode::G);
    Location *ltemp = returnLoc;
    codeGenerator->GenAssign(ltemp, rtemp);
}

void GenCode::handleLValue(LValue * l){
    printf("can't be accessed \n");
}

// 一起处理
void GenCode::handleThis(This * t){
    printf("I am This\n");
}


/**
 * 读写需要区分为两种情况处理
 *
 */
void GenCode::handleArrayAccess(ArrayAccess * a){
    // EmitAddr(cg);
    // 获取base的位置
    // 令人窒息的处理方法， FieldAccess的参数传递

    Location *b;
    Location *s;
    if(storeLValue){
        storeLValue = false;
        a->base->handle(GenCode::G); b = returnLoc;
        a->subscript->handle(GenCode::G); s = returnLoc;
        storeLValue = true;
    }else{
        a->base->handle(GenCode::G); b = returnLoc;
        a->subscript->handle(GenCode::G); s = returnLoc;
    }
    // EmitRuntimeSubscriptCheck(cg, b, s); 动态检查， 马上添加

    // 计算出来具体位置
    Location *con = codeGenerator->GenLoadConstant(CodeGenerator::VarSize);
    Location *num = codeGenerator->GenBinaryOp("*", s, con);
    Location *off = codeGenerator->GenBinaryOp("+", num, con);
    s = codeGenerator->GenBinaryOp("+", b, off);

    if(storeLValue){
        codeGenerator->GenStore(s, assignLocPara);
        returnLoc = s;
        return; // 不认为需要继续执行下面语句
    }

    returnLoc = codeGenerator->GenLoad(s);
}


void GenCode::handleFieldAccess(FieldAccess * f){
    if(storeLValue){
        if(f->base == NULL){
            Location *loc = getMemLoc(f->field->name);
            if (loc->GetSegment() != classRelative) {
                codeGenerator->GenAssign(loc, assignLocPara); // rloc 参数通过 returnLoc 传递
                return;
            }
            Location *This = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
            codeGenerator->GenStore(This, assignLocPara, loc->GetOffset());
            return;
        }else{

            storeLValue = false;
            f->base->handle(GenCode::G);
            storeLValue = true;
            Location * baseVarDecl = returnLoc;

            f->base->handle(GetType::T);

            NamedType * n = dynamic_cast<NamedType *>(exprType);
            ClassDecl * classDecl = dynamic_cast<ClassDecl*>(getGlobalDecl(n->id->name));
            VarDecl * v = getMemberVar(classDecl, f->field->name);

            int fieldOffset = v->memOffset;
            codeGenerator->GenStore(baseVarDecl, assignLocPara, fieldOffset);
            returnLoc = baseVarDecl;
        }
    }else{
        if (f->base == NULL){
            Location *loc = getMemLoc(f->field->name);
            if (loc->GetSegment() != classRelative){
                returnLoc = loc;
                return;
            }
            Location *This = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
            returnLoc = codeGenerator->GenLoad(This, loc->GetOffset());
            return;
        }

            f->base->handle(GenCode::G);
            Location * baseVarDecl = returnLoc;

            f->base->handle(GetType::T);
            NamedType * n = dynamic_cast<NamedType *>(exprType);
            ClassDecl * classDecl = dynamic_cast<ClassDecl*>(getGlobalDecl(n->id->name));
            VarDecl * v = getMemberVar(classDecl, f->field->name);

            int fieldOffset = v->memOffset;
            codeGenerator->GenLoad(baseVarDecl, fieldOffset);
            returnLoc = baseVarDecl;
    }
}

void GenCode::handleCall(Call * c){
    if(isSysCall(c)){
        // 首先检查是否为系统调用的　length !
        // 由于第一个位置保存数组的长度，所以直接获取对应地址即可
        c->base->handle(GenCode::G);
        returnLoc = codeGenerator->GenLoad(returnLoc);
        return;
    }else{
        // 依次分析所有的参数
        List<Location*> *params = new List<Location*>;
        for (int i = 0, n = c->actuals->NumElements(); i < n; ++i){
            c->actuals->Nth(i)->handle(GenCode::G);
            params->Append(returnLoc);
        }

        int n = params->NumElements();
        for (int i = n-1; i >= 0; --i)
            codeGenerator->GenPushParam(params->Nth(i));

        Location *ret;
        // 获取对应的函数
        FnDecl * d = getFnDeclByCall(c);

        /** 由于函数的继承采用同名就是必定override， 即使获取到的函数是parent 的
         *  函数，但是两者的便宜相同，所以也是调用同一个函数
         */
        if (!d->isMethod) {
            ret = codeGenerator->GenLCall(d->label->c_str(), d->returnType != Type::nullType);
            codeGenerator->GenPopParams(n * CodeGenerator::VarSize);
        } else {
            Location *b;
            if (c->base != NULL){
                c->base->handle(GenCode::G);
                b = returnLoc;
            } else{
                b = new Location(fpRelative, CodeGenerator::OffsetToFirstParam, "this");
            }

            codeGenerator->GenPushParam(b);
            Location *vtable = codeGenerator->GenLoad(b);
            int methodOffset = d->vtblOffset; // 预处理的添加
            Location *faddr = codeGenerator->GenLoad(vtable, methodOffset); // 没有看懂为什么
            ret = codeGenerator->GenACall(faddr, d->returnType != Type::nullType);
            codeGenerator->GenPopParams((n+1) * CodeGenerator::VarSize);
        }
        returnLoc = ret;
    }
}

void GenCode::handleNewExpr(NewExpr * n){
    // 获取class类型的声明
    Decl *d = getGlobalDecl(n->cType->id->name);
    Assert(d != NULL);

    // 分析class的时候 需要获取对应constant的大小
    // 类的大小不包含的函数，放到vtable的位置处理
    ClassDecl * cd = dynamic_cast<ClassDecl *>(getGlobalDecl(n->cType->id->name));
    Location *s = codeGenerator->GenLoadConstant(cd->memOffset / CodeGenerator::VarSize);
    Location *c = codeGenerator->GenLoadConstant(CodeGenerator::VarSize);

    Location *mem = codeGenerator->GenBuiltInCall(Alloc, codeGenerator->GenBinaryOp("+", c, s));
    codeGenerator->GenStore(mem, codeGenerator->GenLoadLabel(n->cType->id->name));

    returnLoc = mem;
}

void GenCode::handleNewArrayExpr(NewArrayExpr * n){
    n->size->handle(GenCode::G);
    Location *s = returnLoc;
    Location *c = codeGenerator->GenLoadConstant(CodeGenerator::VarSize);

    // 动态检查，
    // EmitRuntimeSizeCheck(cg, s);
    // 类似于Java的数组，开始的位置含有一个长度标识符

    Location * mul = codeGenerator->GenBinaryOp("*", s, c);
    Location * ret = codeGenerator->GenBuiltInCall(Alloc, codeGenerator->GenBinaryOp("+", c, mul));

    codeGenerator->GenStore(ret, s);
    returnLoc = ret;
}

void GenCode::handleReadIntegerExpr(ReadIntegerExpr * r){
    returnLoc = codeGenerator->GenBuiltInCall(ReadInteger);
}
void GenCode::handleReadLineExpr(ReadLineExpr * r){
    returnLoc = codeGenerator->GenBuiltInCall(ReadLine);
}
void GenCode::handleDecl(Decl * d){
    printf("I am Decl, I can't be accessed\n");
}

void GenCode::handleVarDecl(VarDecl * v){
    // 向下检查是否为nameType
}



void GenCode::handleClassMember(ClassDecl * c){
    c->memOffset = CodeGenerator::OffsetToFirstField;
    c->vtblOffset = CodeGenerator::OffsetToFirstMethod;
    c->vtable = new Hashtable<FnLabel *>();

    // 递归处理继承
    if (c->extends != NULL) {
        ClassDecl *d = dynamic_cast<ClassDecl*>(getGlobalDecl(c->extends->id->name));
        Assert(d != NULL);

        // 查看extends 是否检查过
        if(d->vtable == NULL)
            handleClassMember(d);
        c->memOffset += d->memOffset;
        c->vtblOffset += d->vtblOffset;

        // 复制extends的vtabls
        c->vtable->deepCopy(d->vtable);
    }

    // 为变量添加自己的位置，用于之后的分析
    for (int i = 0, n = c->members->NumElements(); i < n; ++i) {
        VarDecl *d = dynamic_cast<VarDecl*>(c->members->Nth(i));
        if (d == NULL) continue;
        d->memOffset = c->memOffset;
        c->memOffset += CodeGenerator::VarSize;
    }

    // 标记和处理函数
    // 显然不满足动态绑定的处理，添加一个Hashtable 用于处理
    for (int i = 0, n = c->members->NumElements(); i < n; ++i) {
        FnDecl *d = dynamic_cast<FnDecl*>(c->members->Nth(i));
        if (d == NULL) continue;
        d->isMethod = true;

        // 注入标签
        std::string prefix;
        prefix += c->id->name;
        prefix += ".";
        d->label->insert(0, prefix);

        // 查找vtable
        FnLabel * fnLabel = c->vtable->Lookup(d->id->name);
        if(fnLabel == NULL){
            d->vtblOffset = c->vtblOffset;

            c->vtblOffset += CodeGenerator::VarSize;
            c->vtable->Enter(d->id->name, new FnLabel(d->vtblOffset, d->label->c_str()));
        }else{
            // 更新其中label表格, 确定FnDecl的位置
            d->vtblOffset = fnLabel->offset;
            FnLabel * nl = new FnLabel(fnLabel->offset, d->label->c_str());
            c->vtable->Enter(d->id->name, nl);
        }
    }
}

void GenCode::handleClassDecl(ClassDecl * c){
    curClass = c;

    auto var = new Hashtable<Location *>();
    scope.push_back(var);
    auto nameVar = new Hashtable<VarDecl *>();
    nameScope->push_back(nameVar);

    for (int i = 0, n = c->members->NumElements(); i < n; ++i){
        Decl * d = c->members->Nth(i);
        VarDecl * v = dynamic_cast<VarDecl *>(d);
        if(v == NULL) continue;
        var->Enter(v->id->name, new Location(classRelative, v->memOffset, v->id->name));
    }

    for (int i = 0, n = c->members->NumElements(); i < n; ++i)
        c->members->Nth(i)->handle(GenCode::G);

    // 从vtable中间
    List<const char*> *labels = new List<const char*>;
    Iterator<FnLabel *> iter = c->vtable->GetIterator();
    vector<FnLabel *> vec;
    FnLabel * fl;
    while((fl = iter.GetNextValue()) != NULL) vec.push_back(fl);
    CompareFn com;
    sort(vec.begin(), vec.end(), com);
    for(FnLabel * f : vec){
        labels->Append(f->label);
    }

    // 创建vtable
    codeGenerator->GenVTable(c->id->name, labels);

    scope.pop_back();
    nameScope->pop_back();
    curClass = NULL;
}

void GenCode::handleInterfaceDecl(InterfaceDecl * i){
    printf("I am InterfaceDecl, I am supported !\n");
}

void GenCode::handleFnDecl(FnDecl * f){
    int offset = CodeGenerator::OffsetToFirstParam;
    auto var = new Hashtable<Location *>();
    scope.push_back(var);

    auto nameVar = new Hashtable<VarDecl *>();
    nameScope->push_back(nameVar);


    if (f->isMethod)
        offset += CodeGenerator::VarSize;

    // 参数进入stack中间
    for (int i = 0, n = f->formals->NumElements(); i < n; ++i) {
        VarDecl *d = f->formals->Nth(i);
        Location *loc = new Location(fpRelative, offset, d->id->name);
        var->Enter(d->id->name, loc);
        offset += CodeGenerator::VarSize;

        if(!BuildSymbol::B->isBaseType(d->type))
            nameVar->Enter(d->id->name, d);
    }

    if (f->body != NULL) {
        // label 的理解 ！
        codeGenerator->GenLabel(f->label->c_str());
        codeGenerator->GenBeginFunc()->SetFrameSize(16);
        f->body->handle(GenCode::G);
        codeGenerator->GenEndFunc();
    }
    scope.pop_back();
    nameScope->pop_back();
}
