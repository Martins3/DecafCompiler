/* File: ast_stmt.h
* ----------------
* The Stmt class and its subclasses are used to represent
* statements in the parse tree.  For each statment in the
* language (for, if, return, etc.) there is a corresponding
* node class for that construct.
*
* pp3: You will need to extend the Stmt classes to implement
* semantic analysis for rules pertaining to statements.
*/
#ifndef _H_ast_stmt
#define _H_ast_stmt
#include "list.h"
#include "ast.h"
#include "Handler.hpp"

class Program : public Node
{
public:
    virtual void handle(Handler * handler) {
        handler->handleProgram(this);
    }
public:
    List<Decl*> *decls;
public:
    Program(List<Decl*> *declList);
};
class Stmt : public Node
{
public:
    virtual void handle(Handler * handler) {
        handler->handleStmt(this);
    }
public:
    Stmt() : Node() {}
    Stmt(yyltype loc) : Node(loc) {}
};
class StmtBlock : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleStmtBlock(this);
    }
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
};
class ConditionalStmt : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleConditionalStmt(this);
    }
    Expr *test;
    Stmt *body;
public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
};
class LoopStmt : public ConditionalStmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleLoopStmt(this);
    }
public:
    LoopStmt(Expr *testExpr, Stmt *body)
        : ConditionalStmt(testExpr, body) {}
};
class ForStmt : public LoopStmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleForStmt(this);
    }
    Expr *init, *step;
public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
};
class WhileStmt : public LoopStmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleWhileStmt(this);
    }
public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
};
class IfStmt : public ConditionalStmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleIfStmt(this);
    }
    Stmt *elseBody;
public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
};
class BreakStmt : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleBreakStmt(this);
    }
public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
};
class ReturnStmt : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleReturnStmt(this);
    }
    Expr *expr;
public:
    ReturnStmt(yyltype loc, Expr *expr);
};
class PrintStmt : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handlePrintStmt(this);
    }
    List<Expr*> *args;
public:
    PrintStmt(List<Expr*> *arguments);
};
#endif
