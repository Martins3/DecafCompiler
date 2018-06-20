#include <iostream>
using namespace std;
#include "./BuildSymbol.hpp"

BuildSymbol *BuildSymbol::B   = new BuildSymbol();

void print_type(Type* t){
    NamedType * nt = dynamic_cast<NamedType *>(t);
    Assert(nt != NULL);
    printf("[%s]\n", nt->id->name);
}

bool no_error(Type * lt, Type * rt){
    return lt != Type::errorType && rt != Type::errorType;
}

Decl * BuildSymbol::checkOpenScope(const char * name){
    // 反向查找实现屏蔽
    for(auto i = scope.rbegin(); i != scope.rend(); i ++ ){
        Decl * t = (*i)->Lookup(name);
        if(t != NULL) return t;
    }
    return NULL;
}

bool BuildSymbol::checkMisMatch(List<VarDecl*> * superPara, List<VarDecl *> * childPara){
    // length
    int superSize = superPara->NumElements();
    int childSize = childPara->NumElements();
    if(superSize != childSize) return false;

    // type equal
    for (int i = 0; i < superSize; ++i) {
        VarDecl * superVar =  superPara->Nth(i);
        VarDecl * childVar = childPara->Nth(i);
        if(!isTypeEqual(superVar->type, childVar->type)){
            return false;
        }
    }
    return true;
}

bool BuildSymbol::checkMisMatch(Identifier * id, FnDecl * fn, List<Expr *> * arguments){
    List<VarDecl*> * parameters  =  fn->formals;
    int paraSize = parameters->NumElements();
    int argsSize = arguments->NumElements();
    if(paraSize != argsSize){
        ReportError::NumArgsMismatch(id, paraSize, argsSize);
        return false;
    }

    for (int j = 0; j < paraSize; ++j) {
        arguments->Nth(j)->handle(BuildSymbol::B);
        Type * expType =fn->formals->Nth(j)->type;
        if(!isTypeCompatiable(expType, exprType)){
            ReportError::ArgMismatch(arguments->Nth(j), j + 1, exprType, expType);
            return false;
        }
    }
    return true;
}

Hashtable<Decl*> * BuildSymbol::checkInterface(InterfaceDecl * in){
    // 仅仅检查名称是否冲突，参数列表不负责
    Hashtable<Decl*> * mem = memberDecls.Lookup(in->id->name);
    if(mem == NULL){
        mem = checkDeclConflict(in->members);
    }
    memberDecls.Enter(in->id->name, mem);
    return mem;
}

Hashtable<Decl*> * BuildSymbol::checkClass(ClassDecl * d){

    // class and interface : both included !
    Hashtable<Decl*> * mem = memberDecls.Lookup(d->id->name);
    if(mem == NULL){
        // extends
        if(d->extends != NULL){
            ClassDecl * superClass = dynamic_cast<ClassDecl *>(scope[0]->Lookup(d->extends->id->name));
            if(superClass == NULL){
                ReportError::IdentifierNotDeclared(d->extends->id, reasonT::LookingForClass);
            }else{
                Hashtable<Decl * > * supDecl =  checkClass(superClass);
                mem = new Hashtable<Decl *>();
                mem->deepCopy(supDecl);
            }
        }

        // self　装入检查
        if(mem == NULL) mem = new Hashtable<Decl *>();
        int size = d->members->NumElements();
        for (int i = 0; i < size; ++i) {
            Decl * childDecl = d->members->Nth(i);
            const char * name = childDecl->id->name;

            VarDecl * childVarDecl  =  dynamic_cast<VarDecl *>(childDecl);
            FnDecl * childFnDecl = dynamic_cast<FnDecl *>(childDecl);
            Assert(childVarDecl != NULL || childFnDecl != NULL);

            Decl * pd = mem->Lookup(name);
            if(childVarDecl != NULL){
                if(pd != NULL){
                    ReportError::DeclConflict(childVarDecl, pd);
                    continue;
                }
            }else{
                if(pd != NULL){
                    FnDecl * fpd = dynamic_cast<FnDecl *>(pd);
                    if(fpd == NULL){
                        ReportError::DeclConflict(childFnDecl, pd);
                        continue;
                    }else{
                        if(!checkMisMatch(fpd->formals, childFnDecl->formals)){
                            ReportError::OverrideMismatch(childFnDecl);
                            continue;
                        }
                    }
                }
            }
            mem->Enter(childDecl->id->name, childDecl);// 子类压制父类
        }


        // interface
        int interfaceSize = d->implements->NumElements();
        for (int i = 0; i < interfaceSize; ++i) {
            Identifier * in = d->implements->Nth(i)->id;
            InterfaceDecl * interface = dynamic_cast<InterfaceDecl *>(scope[0]->Lookup(in->name));

            if(interface == NULL){
                ReportError::IdentifierNotDeclared(in, reasonT::LookingForInterface); // 不够清真
            }else{
                int memSize = interface->members->NumElements();

                for (int ii = 0; ii < memSize; ++ii) {
                    FnDecl * prototype = dynamic_cast<FnDecl*>(interface->members->Nth(ii));
                    Assert(prototype != NULL); //　词法保证
                    // 此处报错很微妙！
                    FnDecl * implement  = dynamic_cast<FnDecl *>(mem->Lookup(prototype->id->name));
                    if(implement == NULL){
                        ReportError::InterfaceNotImplemented(d, d->implements->Nth(i)); // caution ! new NamedType()
                    }else{
                        if(!checkMisMatch(prototype->formals, implement->formals)){
                            ReportError::OverrideMismatch(implement); // 参数不一致
                        }
                    }

                }
            }

        }

        memberDecls.Enter(d->id->name, mem);
    }
    return mem;
}

bool BuildSymbol::isBaseType(Type * t){
    // 删除error 不是基本类型
    // 出现就是必定类型不兼容
    if(t == Type::boolType) return true;
    if(t == Type::doubleType) return true;
    if(t == Type::stringType) return true;
    if(t == Type::intType) return true;
    if(t == Type::nullType) return true;
    if(t == Type::errorType) return true;
    if(t == Type::voidType) return true;
    return false;
}

bool BuildSymbol::isTypeEqual(Type * src, Type * dest){
    // 基本类型 比较指针
    if(isBaseType(src) && isBaseType(dest)) return src ==  dest;
    if(!isBaseType(src) && !isBaseType(dest)){

        ArrayType * as = dynamic_cast<ArrayType *>(src);
        ArrayType * ad = dynamic_cast<ArrayType *>(dest);

        NamedType * ns = dynamic_cast<NamedType *>(src);
        NamedType * nd = dynamic_cast<NamedType *>(dest);

        if(as == NULL && ad == NULL){
            Assert(ns != NULL && nd != NULL);
            // NamedType　比较字符串　class 和 interface 都是在最高层
            // why clang check failed !
            return strcmp(ns->id->name, nd->id->name) == 0;
        }

        if(as != NULL && ad != NULL){
            // ArrayType 递归比较
            Assert(ns == NULL && nd == NULL);
            return isTypeEqual(as->elemType, ad->elemType);
        }

        return false;
    }
    return false;
}

stack<const char *> * BuildSymbol::getSuperClass(const char * className){
    // 接口类型　应该拒绝调用　才可以！
    Assert(this->scope.size() > 0);
    ClassDecl * c = dynamic_cast<ClassDecl*>(scope[0]->Lookup(className));
    if(c == NULL) return new stack<const char *>(); // interface 类型之间的赋值会调用此数值
    stack<const char *> * s = new stack<const char *>();
    while(c->extends != NULL){
        const char * en = c->extends->id->name;
        s->push(en);
        c = dynamic_cast<ClassDecl *>(scope[0]->Lookup(en));
        if(c == NULL) break; // 检查到不存在，直接放弃，但是未知superClass 添加到列表中
        // 如果有，那么Interface 也添加进来
        int size = c->implements->NumElements();
        for (int i = 0; i < size; ++i) {
            s->push(c->implements->Nth(i)->id->name);
        }
    }
    return s;
    // 非要使用stack 吗?
}

bool BuildSymbol::isTypeCompatiable(Type * left, Type * right){

    NamedType * l = dynamic_cast<NamedType *>(left);
    NamedType * r = dynamic_cast<NamedType *>(right);


    if(l == NULL || r == NULL){
        // null 和所有的全部兼容
        if(right == Type::nullType && l != NULL){ return true; }
        if(left == Type::nullType && r != NULL){ return true; }
        return isTypeEqual(left, right);
    }

    if(strcmp(l->id->name, r->id->name) == 0) return true;



    // 递归的查找继承的类，同时添加对应类中间的implements进来
    stack<const char *> * s = getSuperClass(r->id->name);
    while(!s->empty()){
        if(strcmp(s->top(), l->id ->name) == 0) return true;
        s->pop();
    }

    // 遍历interface
    ClassDecl* c = dynamic_cast<ClassDecl *>(scope[0]->Lookup(r->id->name));
    if(c == NULL) return false; // 右侧class 不存在
    List<NamedType *> * ins = c->implements;
    int size = ins->NumElements();
    for (int i = 0; i < size; ++i) {
        if(strcmp(l->id->name, ins->Nth(i)->id->name) == 0){
            return true;
        }
    }
    return false;
}

void BuildSymbol::print_hashtables(){
    for(auto i = scope.begin(); i != scope.end(); i ++ ){
        (*i)->printKeys();
    }
}

bool BuildSymbol::CheckIdentifierNotDeclared(Identifier * id, reasonT typeNeed){
        Decl * t = checkOpenScope(id->name);
        ClassDecl * c;
        InterfaceDecl * in;
        VarDecl * v;
        FnDecl * f;
        if(t != NULL){
            // 找到了，　但是需要检查类型
            switch (typeNeed) {
                case reasonT::LookingForType:
                    c = dynamic_cast<ClassDecl*>(t);
                    in = dynamic_cast<InterfaceDecl*>(t);
                    if(c == NULL && in == NULL){
                        ReportError::IdentifierNotDeclared(id, typeNeed);
                        return false;
                    } else{
                        return true;
                    }
                case reasonT::LookingForVariable:
                    v = dynamic_cast<VarDecl *>(t);
                    if(v == NULL){
                        ReportError::IdentifierNotDeclared(id, typeNeed);
                        return false;
                    } else{
                        return true;
                    }
                case reasonT::LookingForFunction:
                    f = dynamic_cast<FnDecl *>(t);
                    if(f == NULL){
                        ReportError::IdentifierNotDeclared(id, typeNeed);
                        return false;
                    } else{
                        return true;
                    }
                case reasonT::LookingForInterface:
                    printf("%d", typeNeed);
                    Assert(false);
                    return false;
                case reasonT::LookingForClass:
                    c = dynamic_cast<ClassDecl *>(t);
                    if(c == NULL){
                        ReportError::IdentifierNotDeclared(id, typeNeed);
                        return false;
                    } else{
                        return true;
                    }
                default:
                    // todo
                    Assert(false);
                    return false;
            }
        }else{
            ReportError::IdentifierNotDeclared(id, typeNeed);
            return false;
        }
}

// unuseful
void BuildSymbol::addDecl(Decl * v){
    const char * name = v->id->name;
    Hashtable<Decl*> * h = this->scope.back();
    Decl * pd = h->Lookup(name);
    if(pd != NULL) {
        Decl * npd = dynamic_cast<Decl*>(pd);
        Assert(npd != NULL);
        ReportError::DeclConflict(v, npd);
    } else {
        h->Enter(v->id->name, v);
    }
}

Hashtable<Decl*> * BuildSymbol::checkDeclConflict(List<VarDecl*> * declList){
    List<Decl*> * l = new List<Decl*>(); //　two list !
    int size = declList->NumElements();
    for (int i = 0; i < size; ++i){ l->Append(declList->Nth(i));}
    return checkDeclConflict(l);
}

Hashtable<Decl*> * BuildSymbol::checkDeclConflict(List<Decl*> * declList){
    // only check key !
    Hashtable<Decl*> * h = new Hashtable<Decl*>();
    int size = declList->NumElements();
    for (int i = 0; i < size; ++i) {
        Decl * d = declList->Nth(i);
        const char * name = d->id->name;
        Decl * pd = h->Lookup(name);
        if(pd != NULL) {
            ReportError::DeclConflict(d, pd);
        } else {
            h->Enter(d->id->name, d);
        }
    }
    return h;
}


void BuildSymbol::handleProgram(Program * p) {

    Hashtable<Decl*> * h = checkDeclConflict(p->decls);
    this->scope.push_back(h);


    int size = p->decls->NumElements();
    // dive into
    for (int i = 0; i < size; ++i) {
        p->decls->Nth(i)->handle(BuildSymbol::B);
    }

    this->scope.pop_back();

}
void BuildSymbol::handleStmt(Stmt * s) {
    Assert(false);
}

// 函数体
void BuildSymbol::handleStmtBlock(StmtBlock * s) {

    // 分析decls 重复
    Hashtable<Decl*> * h = checkDeclConflict(s->decls);
    this->scope.push_back(h);


    // 分析所有decl
    int size = s->decls->NumElements();
    for (int i = 0; i < size; ++i) {
        s->decls->Nth(i)->handle(BuildSymbol::B);
    }

    // 追条分析所有的Stmts
    size = s->stmts->NumElements();
    for (int i = 0; i < size; ++i) {
        s->stmts->Nth(i)->handle(BuildSymbol::B);
    }

    this->scope.pop_back();
}

void BuildSymbol::handleConditionalStmt(ConditionalStmt * c) {
    Assert(false);
}
void BuildSymbol::handleLoopStmt(LoopStmt * l) {
    Assert(false);
}

void BuildSymbol::handleForStmt(ForStmt * f) {
    // 没有新的decl，　不影响作用域
    // break 是 stmt loopLevel　位置随意
    loopLevel ++;
    f->init->handle(BuildSymbol::B);
    f->test->handle(BuildSymbol::B);
    if(exprType != Type::boolType)
        ReportError::TestNotBoolean(f->test);
    f->step->handle(BuildSymbol::B);
    f->body->handle(BuildSymbol::B);
    loopLevel --;
}
void BuildSymbol::handleWhileStmt(WhileStmt * w) {
    loopLevel ++;
    w->test->handle(BuildSymbol::B);
    if(exprType != Type::boolType)
        ReportError::TestNotBoolean(w->test);
    w->body->handle(BuildSymbol::B);
    loopLevel --;
}

void BuildSymbol::handleIfStmt(IfStmt * i) {
    i->test->handle(BuildSymbol::B);
    if(exprType != Type::boolType)
        ReportError::TestNotBoolean(i->test);
    i->body->handle(BuildSymbol::B);
    if(i->elseBody != NULL) i->elseBody->handle(BuildSymbol::B);
}

void BuildSymbol::handleBreakStmt(BreakStmt * b) {
    Assert(loopLevel >= 0);
    if(!loopLevel)
        ReportError::BreakOutsideLoop(b);
}

void BuildSymbol::handleReturnStmt(ReturnStmt * r) {
    r->expr->handle(BuildSymbol::B);
    if(!isTypeCompatiable(this->returnType, exprType))
        ReportError::ReturnMismatch(r, exprType, this->returnType);
}

void BuildSymbol::handlePrintStmt(PrintStmt * p) {
    int size = p->args->NumElements();
    for (int i = 0; i < size; ++i) {
        p->args->Nth(i)->handle(BuildSymbol::B);
        if(!(exprType == Type::intType || exprType == Type::stringType || exprType == Type::boolType || exprType == Type::errorType)){
            ReportError::PrintArgMismatch(p->args->Nth(i), i + 1, exprType);
        }
    }
}
void BuildSymbol::handleType(Type * t) {
    // 基本类型将会访问此函数
}
void BuildSymbol::handleNamedType(NamedType * n) {
    // 报错信息过于简单，实际上需要一定检查
    CheckIdentifierNotDeclared(n->id, handleNamedTypePara);
    handleNamedTypePara = reasonT::LookingForType;
}
void BuildSymbol::handleArrayType(ArrayType * a) {
    a->elemType->handle(BuildSymbol::B);
}
void BuildSymbol::handleNode(Node * n) {
    Assert(false);
}

void BuildSymbol::handleIdentifier(Identifier * i) {
    Assert(false);
}
void BuildSymbol::handleError(Error * e) {
    printf("I am Error\n");
}
void BuildSymbol::handleExpr(Expr * e) {
    Assert(false);
}

void BuildSymbol::handleEmptyExpr(EmptyExpr * e) {
    this->exprType = Type::voidType;
}

void BuildSymbol::handleIntConstant(IntConstant * i) {
    this->exprType = Type::intType;
}
void BuildSymbol::handleDoubleConstant(DoubleConstant * d) {
    this->exprType = Type::doubleType;
}
void BuildSymbol::handleBoolConstant(BoolConstant * b) {
    this->exprType = Type::boolType;
}
void BuildSymbol::handleStringConstant(StringConstant * s) {
    this->exprType = Type::stringType;
}
void BuildSymbol::handleNullConstant(NullConstant * n) {
    this->exprType = Type::nullType;
}

void BuildSymbol::handleOperator(Operator * o) {
    // 从语义的角度上不应该含有
    Assert(false);
}

void BuildSymbol::handleCompoundExpr(CompoundExpr * c) {
    Assert(false);
}
void BuildSymbol::handleArithmeticExpr(ArithmeticExpr * a) {
    if(a->left == NULL){
        a->right->handle(BuildSymbol::B);
        Type * rt = exprType;

        if(rt != Type::intType && rt != Type::doubleType){
            if(no_error(rt, NULL)){
                ReportError::IncompatibleOperand(a->op, rt);
                exprType = Type::errorType;
                return;
            }
        }
        return;
    }
    a->left->handle(BuildSymbol::B);
    Type * lt = exprType;
    a->right->handle(BuildSymbol::B);
    Type * rt = exprType;

    if(!isTypeEqual(lt, rt)){
        if(no_error(lt, rt)){
            ReportError::IncompatibleOperands(a->op, lt, rt);
            exprType = Type::errorType;
            return;
        }
    }


    if(lt != Type::intType && lt != Type::doubleType){
        if(no_error(lt, rt)){
            ReportError::IncompatibleOperands(a->op, lt, rt);
            exprType = Type::errorType;
            return;
        }
    }
}

void BuildSymbol::handleRelationalExpr(RelationalExpr * a) {
    a->left->handle(BuildSymbol::B);
    Type * lt = exprType;
    a->right->handle(BuildSymbol::B);
    Type * rt = exprType;

    if(!isTypeEqual(lt, rt)){
        if(no_error(lt, rt)){
            ReportError::IncompatibleOperands(a->op, lt, rt);
            exprType = Type::errorType;
            return;
        }
    }

    if(lt != Type::intType && lt != Type::doubleType){
        if(no_error(lt, rt)){
            ReportError::IncompatibleOperands(a->op, lt, rt);
            exprType = Type::errorType;
            return;
        }
    }

    exprType = Type::boolType;
}

void BuildSymbol::handleEqualityExpr(EqualityExpr * e) {
    e->left->handle(BuildSymbol::B);
    Type * lt = exprType;
    e->right->handle(BuildSymbol::B);
    Type * rt = exprType;

    // 相等性测试含有特殊处理，NULL 兼容

    if(rt == Type::nullType){
        NamedType * nt = dynamic_cast<NamedType *>(lt);
        if(nt != NULL){
            exprType = Type::boolType;
            return;
        }
    }

    if(lt == Type::nullType){
        NamedType * nt = dynamic_cast<NamedType *>(rt);
        if(nt != NULL){
            exprType = Type::boolType;
            return;
        }
    }

    if(!isTypeCompatiable(lt, rt) || lt == Type::voidType){
        ReportError::IncompatibleOperands(e->op, lt, rt);
    }

    exprType = Type::boolType;
}

void BuildSymbol::handleLogicalExpr(LogicalExpr * l) {
    if(l-> left == NULL){
        l->right->handle(BuildSymbol::B);
        Type * rt = exprType;

        if(rt != Type::boolType){
            if(no_error(rt, NULL))
                ReportError::IncompatibleOperand(l->op, rt);
        }
        exprType = Type::boolType;
        return;
    }
    l->left->handle(BuildSymbol::B);
    Type * lt = exprType;
    l->right->handle(BuildSymbol::B);
    Type * rt = exprType;

    if(lt != Type::boolType || rt != Type::boolType){
        if(no_error(lt, rt))
            ReportError::IncompatibleOperands(l->op, lt, rt);
    }

    exprType = Type::boolType;
}
void BuildSymbol::handleAssignExpr(AssignExpr * a) {
    a->left->handle(BuildSymbol::B);
    Type * lt = exprType;
    a->right->handle(BuildSymbol::B);
    Type * rt = exprType;

    if(!isTypeCompatiable(lt, rt)){
        if(no_error(lt, rt)){
            ReportError::IncompatibleOperands(a->op, lt, rt);
        }
        exprType = Type::errorType;
    }

    exprType = lt;
}

void BuildSymbol::handleLValue(LValue * l) {
    Assert(false);
}
void BuildSymbol::handleThis(This * t) {
    // 检查是否在类中间
    if(!inClass){
        ReportError::ThisOutsideClassScope(t);
        exprType = Type::errorType;
        return;
    }

    // 返回NamedType类型
    Assert(curClass != NULL);
    exprType = new NamedType(curClass);
}
void BuildSymbol::handleArrayAccess(ArrayAccess * a) {
    a->base->handle(BuildSymbol::B);
    ArrayType * baseType = dynamic_cast<ArrayType *>(exprType);
    if(baseType == NULL){
        ReportError::BracketsOnNonArray(a->base);
        exprType = Type::errorType;
        return;
    }
    Type * t = baseType->elemType;
    a->subscript->handle(BuildSymbol::B);
    if(exprType != Type::intType){
        ReportError::SubscriptNotInteger(a->subscript);
        exprType = Type::errorType;
        return;
    }

    exprType = t;
}


void BuildSymbol::handleFieldAccess(FieldAccess * f) {
    // Caution !
    // 编译时期决定可以访问区间
    // 似乎只要左侧不是this 都是需要报错的
    // NamedType 需要自己new

    if(f->base == NULL){
        // 检查整个开区间的变量声明
        VarDecl * field = dynamic_cast<VarDecl *>(checkOpenScope(f->field->name));
        if(field == NULL){
            ReportError::IdentifierNotDeclared(f->field, reasonT::LookingForVariable);
            exprType = Type::errorType;
            return;
        }
        exprType = field->type;
    }

    else{
        // 确保expr类型是class, base表达式类型是NameType
        // static void FieldNotFoundInBase(Identifier *field, Type *base);
        // static void InaccessibleField(Identifier *field, Type *base);
        f->base->handle(BuildSymbol::B);
        NamedType * baseType = dynamic_cast<NamedType *>(exprType);
        if(baseType == NULL){
            // 不是接口或者类，或者不存在
            ReportError::FieldNotFoundInBase(f->field, exprType);
            exprType = Type::errorType;
        }else{
            Decl * d = checkOpenScope(baseType->id->name);
            Assert(d != NULL);
            ClassDecl * classDecl =  dynamic_cast<ClassDecl *>(d);
            if(classDecl ==  NULL){
                // 编译时期决定可以访问区间， interface没有任何变量, 直接报错
                ReportError::FieldNotFoundInBase(f->field, baseType);
                exprType = Type::errorType;
            }else{
                Hashtable<Decl *> * mem = checkClass(classDecl);
                VarDecl *  var = dynamic_cast<VarDecl *>(mem->Lookup(f->field->name));
                if(var == NULL){
                    ReportError::FieldNotFoundInBase(f->field, baseType);
                    exprType = Type::errorType;
                }else{
                    if(!inClass || strcmp(curClass->name, classDecl->id->name)){
                        ReportError::InaccessibleField(f->field, baseType);
                        exprType = Type::errorType;
                    }else{
                        exprType = var->type;
                    }
                }
            }
        }
    }
}


void BuildSymbol::handleCall(Call * c) {

    //　首先检查参数，然后对应的数值
    int actualSize = c->actuals->NumElements();
    for (int i = 0; i < actualSize; ++i) {
        c->actuals->Nth(i)->handle(BuildSymbol::B);
    }

    // continue check
    if(c->base == NULL){
        FnDecl * fnDecl = dynamic_cast<FnDecl *>(checkOpenScope(c->field->name));
        if(fnDecl == NULL){
            ReportError::IdentifierNotDeclared(c->field, reasonT::LookingForFunction);
            return;
        }else{
            checkMisMatch(c->field, fnDecl, c->actuals);
        }
        exprType = fnDecl->returnType;
        return;
    }else{
        // 类似，但是部分位置含有不同的地方！
        c->base->handle(BuildSymbol::B);
        NamedType * baseType = dynamic_cast<NamedType *>(exprType);
        if(baseType == NULL){
            // 检查是不是array 的模式
            ArrayType * arr = dynamic_cast<ArrayType *>(exprType);
            if(arr != NULL){
                // 只有调用length 函数才可以
                if(strcmp(c->field->name, "length") == 0){
                    // 参数列表必须为空
                    if(c->actuals->NumElements() == 0){
                        exprType = Type::intType;
                        return;
                    }
                }
            }
            ReportError::FieldNotFoundInBase(c->field, exprType);
            exprType = Type::errorType;
            return;
        }else{
            Decl * d = checkOpenScope(baseType->id->name);
            if(d == NULL){
                // base 申明过，而且但是申明的类型不存在, 不要报错，　直接返回
                exprType = Type::errorType;
                return;
            }

            ClassDecl * cDecl = dynamic_cast<ClassDecl *>(d);
            FnDecl * var;
            if(cDecl != NULL){
                Hashtable<Decl *> * mem = checkClass(cDecl);
                var = dynamic_cast<FnDecl *>(mem->Lookup(c->field->name));
            }else{
                InterfaceDecl * inDecl = dynamic_cast<InterfaceDecl *>(d);
                Assert(inDecl != NULL);
                Hashtable<Decl *> * mem = checkInterface(inDecl);
                var = dynamic_cast<FnDecl *>(mem->Lookup(c->field->name));
            }

            if(var == NULL){
                ReportError::FieldNotFoundInBase(c->field, baseType);
                exprType = Type::errorType;
            }else{
                if(checkMisMatch(c->field, var, c->actuals)){
                    exprType = var->returnType;
                    return;
                }
            }
        }
    }
    exprType = Type::errorType;
}

void BuildSymbol::handleNewExpr(NewExpr * n) {
    // 报错信息过于简单！
    handleNamedTypePara = reasonT::LookingForClass;
    n->cType->handle(BuildSymbol::B);
    exprType = n->cType;
}

void BuildSymbol::handleNewArrayExpr(NewArrayExpr * n) {
    n->size->handle(BuildSymbol::B);
    if(exprType != Type::intType)
        ReportError::NewArraySizeNotInteger(n->size);
    n->elemType->handle(BuildSymbol::B);
    exprType = new ArrayType(*(n->location), n->elemType);
}

void BuildSymbol::handleReadIntegerExpr(ReadIntegerExpr * r) {
    exprType = Type::intType;
}

void BuildSymbol::handleReadLineExpr(ReadLineExpr * r) {
    exprType = Type::stringType;
}

void BuildSymbol::handleDecl(Decl * d) {
    Assert(false);
}

void BuildSymbol::handleVarDecl(VarDecl * v) {
    // 检查使用类型是否申明过
    Type * t = v->type;
    t->handle(BuildSymbol::B);
}
void BuildSymbol::handleClassDecl(ClassDecl * c) {
    // 收集当前作用域Decl　创建出来一个新的HashTable, 设置对应的指针
    Hashtable<Decl*> * h = checkClass(c);
    scope.push_back(h);
    inClass = true;
    curClass = c->id;

    int size = c->members->NumElements();
    for (int i = 0; i < size; ++i) {
        c->members->Nth(i)->handle(BuildSymbol::B);
    }

    curClass = NULL;
    inClass = false;
    scope.pop_back();
}

void BuildSymbol::handleInterfaceDecl(InterfaceDecl * in) {
    checkInterface(in); // 没有定义作用域

    int size = in->members->NumElements();
    for (int i = 0; i < size; ++i) {
        in->members->Nth(i)->handle(BuildSymbol::B);
    }
}

void BuildSymbol::handleFnDecl(FnDecl * f) {

    List<VarDecl*> * formals = f ->formals;
    Type *returnType = f->returnType;
    Stmt *body = f->body;

    //　建立table, 处理formals 中间是否重复
    Hashtable<Decl*> * h = checkDeclConflict(formals);
    this->scope.push_back(h);
    int size = formals->NumElements();
    for (int i = 0; i < size; ++i) {
        formals->Nth(i)->handle(BuildSymbol::B);
    }

    //　检查函数返回值是否一致
    //  函数没有办法嵌套, 当进入函数的时候设置类型，离开函数的时候删除类型
    this->returnType = returnType;

    //  向下处理body, 完全交付给stamList处理
    if(body != NULL)
        body->handle(BuildSymbol::B);

    this->returnType = NULL;
    this->scope.pop_back();
}

