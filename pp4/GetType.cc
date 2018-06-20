#include "./GetType.hpp"
#include <iostream>
using namespace std;

GetType * GetType::T = new GetType();
void GetType::handleExpr(Expr * e){
    printf("I am Expr\n");
}

void GetType::handleEmptyExpr(EmptyExpr * e){
    printf("I am EmptyExpr\n");
}

void GetType::handleIntConstant(IntConstant * i){
    printf("I am IntConstant\n");
}
void GetType::handleDoubleConstant(DoubleConstant * d){
    printf("I am DoubleConstant\n");
}

void GetType::handleBoolConstant(BoolConstant * b){
    printf("I am BoolConstant\n");
}

void GetType::handleStringConstant(StringConstant * s){
    printf("I am StringConstant\n");
}

void GetType::handleNullConstant(NullConstant * n){
    printf("I am NullConstant\n");
}

void GetType::handleOperator(Operator * o){
    printf("I am Operator\n");
}

void GetType::handleCompoundExpr(CompoundExpr * c){
    c->right->handle(GetType::G);
}

void GetType::handleArithmeticExpr(ArithmeticExpr * a){
    a->right->handle(GetType::G);
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

void GetType::handleLValue(LValue * l){
    printf("I am LValue\n");
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

void GetType::handleNewExpr(NewExpr * n){ printf("I am NewExpr\n"); }
void GetType::handleNewArrayExpr(NewArrayExpr * n){ printf("I am NewArrayExpr\n"); }
void GetType::handleReadIntegerExpr(ReadIntegerExpr * r){ printf("I am ReadIntegerExpr\n"); }
void GetType::handleReadLineExpr(ReadLineExpr * r){ printf("I am ReadLineExpr\n"); }

