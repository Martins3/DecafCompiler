#include "./GenCode.hpp"
using namespace std;

GetType * GetType::T = new GetType();

void GetType::handleEmptyExpr(EmptyExpr * e){
    exprType = NULL;
}

void GetType::handleIntConstant(IntConstant * i){
    exprType = Type::intType;
}

void GetType::handleDoubleConstant(DoubleConstant * d){
    exprType = Type::doubleType;
}

void GetType::handleBoolConstant(BoolConstant * b){
    exprType = Type::boolType;
}

void GetType::handleStringConstant(StringConstant * s){
    exprType = Type::stringType;
}

void GetType::handleNullConstant(NullConstant * n){
    exprType = Type::nullType;
}

void GetType::handleArithmeticExpr(ArithmeticExpr * a){
    a->right->handle(GetType::T);
}

void GetType::handleRelationalExpr(RelationalExpr * r){
    exprType = Type::boolType;
}

void GetType::handleEqualityExpr(EqualityExpr * e){
    exprType = Type::boolType;
}

void GetType::handleLogicalExpr(LogicalExpr * l){
    exprType = Type::boolType;
}

void GetType::handleAssignExpr(AssignExpr * a){
   a->left->handle(GetType::T);
}

void GetType::handleThis(This * t){
    exprType = new NamedType(curClass->id);
}

void GetType::handleArrayAccess(ArrayAccess * a){
    a->base->handle(GetType::T);
    ArrayType * t = dynamic_cast<ArrayType *>(exprType);
    Assert(t != NULL); // base的类型一定需要是对象数组类型
    exprType = t->elemType;
}

void GetType::handleFieldAccess(FieldAccess * f){
    if(f->base == NULL){
        VarDecl * v = getNameVar(f->field->name);
        exprType = v->type;
    }else{
        // check for Name Type for the base
        // find the type in the Class
        f->base->handle(GetType::T);
        NamedType * n = dynamic_cast<NamedType *>(exprType); //此时base的类型一定是NameType
        ClassDecl * classDecl = dynamic_cast<ClassDecl*>(getGlobalDecl(n->id->name));
        exprType = getMemberVar(classDecl, f->field->name)->type;
    }
}

void GetType::handleCall(Call * c){
    FnDecl * f = getFnDeclByCall(c);
    exprType = f->returnType;
}

void GetType::handleNewExpr(NewExpr * n){
    exprType = n->cType; // 参数是NamedType, 所以直接返回
}

void GetType::handleNewArrayExpr(NewArrayExpr * n){
    exprType = new ArrayType(*(n->location), n->elemType);
}

void GetType::handleReadIntegerExpr(ReadIntegerExpr * r){
    exprType = Type::intType;
}

void GetType::handleReadLineExpr(ReadLineExpr * r){
    exprType = Type::stringType;
}
