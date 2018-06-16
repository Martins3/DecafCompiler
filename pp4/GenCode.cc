#include <iostream>
using namespace std;
#include "./GenCode.hpp"


GenCode * GenCode::G = new GenCode();

void GenCode::handleProgram(Program * p){
    printf("I am Program\n");
}
void GenCode::handleStmt(Stmt * s){
    printf("I am Stmt\n");
}
void GenCode::handleStmtBlock(StmtBlock * s){
    printf("I am StmtBlock\n");
}
void GenCode::handleConditionalStmt(ConditionalStmt * c){
    printf("I am ConditionalStmt\n");
}
void GenCode::handleLoopStmt(LoopStmt * l){
    printf("I am LoopStmt\n");
}
void GenCode::handleForStmt(ForStmt * f){
    printf("I am ForStmt\n");
}
void GenCode::handleWhileStmt(WhileStmt * w){
    printf("I am WhileStmt\n");
}
void GenCode::handleIfStmt(IfStmt * i){
    printf("I am IfStmt\n");
}
void GenCode::handleBreakStmt(BreakStmt * b){
    printf("I am BreakStmt\n");
}
void GenCode::handleReturnStmt(ReturnStmt * r){
    printf("I am ReturnStmt\n");
}
void GenCode::handlePrintStmt(PrintStmt * p){
    printf("I am PrintStmt\n");
}
void GenCode::handleType(Type * t){
    printf("I am Type\n");
}
void GenCode::handleNamedType(NamedType * n){
    printf("I am NamedType\n");
}
void GenCode::handleArrayType(ArrayType * a){
    printf("I am ArrayType\n");
}
void GenCode::handleNode(Node * n){
    printf("I am Node\n");
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
    printf("I am EmptyExpr\n");
}
void GenCode::handleIntConstant(IntConstant * i){
    printf("I am IntConstant\n");
}
void GenCode::handleDoubleConstant(DoubleConstant * d){
    printf("I am DoubleConstant\n");
}
void GenCode::handleBoolConstant(BoolConstant * b){
    printf("I am BoolConstant\n");
}
void GenCode::handleStringConstant(StringConstant * s){
    printf("I am StringConstant\n");
}
void GenCode::handleNullConstant(NullConstant * n){
    printf("I am NullConstant\n");
}
void GenCode::handleOperator(Operator * o){
    printf("I am Operator\n");
}
void GenCode::handleCompoundExpr(CompoundExpr * c){
    printf("I am CompoundExpr\n");
}
void GenCode::handleArithmeticExpr(ArithmeticExpr * a){
    printf("I am ArithmeticExpr\n");
}
void GenCode::handleRelationalExpr(RelationalExpr * r){
    printf("I am RelationalExpr\n");
}
void GenCode::handleEqualityExpr(EqualityExpr * e){
    printf("I am EqualityExpr\n");
}
void GenCode::handleLogicalExpr(LogicalExpr * l){
    printf("I am LogicalExpr\n");
}
void GenCode::handleAssignExpr(AssignExpr * a){
    printf("I am AssignExpr\n");
}
void GenCode::handleLValue(LValue * l){
    printf("I am LValue\n");
}
void GenCode::handleThis(This * t){
    printf("I am This\n");
}
void GenCode::handleArrayAccess(ArrayAccess * a){
    printf("I am ArrayAccess\n");
}
void GenCode::handleFieldAccess(FieldAccess * f){
    printf("I am FieldAccess\n");
}
void GenCode::handleCall(Call * c){
    printf("I am Call\n");
}
void GenCode::handleNewExpr(NewExpr * n){
    printf("I am NewExpr\n");
}
void GenCode::handleNewArrayExpr(NewArrayExpr * n){
    printf("I am NewArrayExpr\n");
}
void GenCode::handleReadIntegerExpr(ReadIntegerExpr * r){
    printf("I am ReadIntegerExpr\n");
}
void GenCode::handleReadLineExpr(ReadLineExpr * r){
    printf("I am ReadLineExpr\n");
}
void GenCode::handleDecl(Decl * d){
    printf("I am Decl\n");
}
void GenCode::handleVarDecl(VarDecl * v){
    printf("I am VarDecl\n");
}
void GenCode::handleClassDecl(ClassDecl * c){
    printf("I am ClassDecl\n");
}
void GenCode::handleInterfaceDecl(InterfaceDecl * i){
    printf("I am InterfaceDecl\n");
}
void GenCode::handleFnDecl(FnDecl * f){
    printf("I am FnDecl\n");
}
