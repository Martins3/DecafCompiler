#ifndef GEN_CODE_H
#define GEN_CODE_H

#include "./Handler.hpp"
#include "./list.h"
#include "./hashtable.hpp"
#include "./ast.h"
#include "./ast_stmt.h"
#include "./ast_decl.h"
#include "./ast_expr.h"
#include "./ast_type.h"
#include "./errors.h"
#include <iostream>
#include <cstdio>
#include <deque>
#include <stack>
#include "hashtable.hpp"

class  GenCode: public Handler{
public:

    static GenCode * G;

    void handleProgram(Program * p);
    void handleStmt(Stmt * s);
    void handleStmtBlock(StmtBlock * s);
    void handleConditionalStmt(ConditionalStmt * c);
    void handleLoopStmt(LoopStmt * l);
    void handleForStmt(ForStmt * f);
    void handleWhileStmt(WhileStmt * w);
    void handleIfStmt(IfStmt * i);
    void handleBreakStmt(BreakStmt * b);
    void handleReturnStmt(ReturnStmt * r);
    void handlePrintStmt(PrintStmt * p);
    void handleType(Type * t);
    void handleNamedType(NamedType * n);
    void handleArrayType(ArrayType * a);
    void handleNode(Node * n);
    void handleIdentifier(Identifier * i);
    void handleError(Error * e);
    void handleExpr(Expr * e);
    void handleEmptyExpr(EmptyExpr * e);
    void handleIntConstant(IntConstant * i);
    void handleDoubleConstant(DoubleConstant * d);
    void handleBoolConstant(BoolConstant * b);
    void handleStringConstant(StringConstant * s);
    void handleNullConstant(NullConstant * n);
    void handleOperator(Operator * o);
    void handleCompoundExpr(CompoundExpr * c);
    void handleArithmeticExpr(ArithmeticExpr * a);
    void handleRelationalExpr(RelationalExpr * r);
    void handleEqualityExpr(EqualityExpr * e);
    void handleLogicalExpr(LogicalExpr * l);
    void handleAssignExpr(AssignExpr * a);
    void handleLValue(LValue * l);
    void handleThis(This * t);
    void handleArrayAccess(ArrayAccess * a);
    void handleFieldAccess(FieldAccess * f);
    void handleCall(Call * c);
    void handleNewExpr(NewExpr * n);
    void handleNewArrayExpr(NewArrayExpr * n);
    void handleReadIntegerExpr(ReadIntegerExpr * r);
    void handleReadLineExpr(ReadLineExpr * r);
    void handleDecl(Decl * d);
    void handleVarDecl(VarDecl * v);
    void handleClassDecl(ClassDecl * c);
    void handleInterfaceDecl(InterfaceDecl * i);
    void handleFnDecl(FnDecl * f);
};
#endif
