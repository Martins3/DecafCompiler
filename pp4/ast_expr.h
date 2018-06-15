/* File: ast_expr.h
* ----------------
* The Expr class and its subclasses are used to represent
* expressions in the parse tree.  For each expression in the
* language (add, call, New, etc.) there is a corresponding
* node class for that construct.
*
* pp3: You will need to extend the Expr classes to implement
* semantic analysis for rules pertaining to expressions.
*/
#ifndef _H_ast_expr
#define _H_ast_expr
#include "ast.h"
#include "ast_stmt.h"
#include "list.h"
class Expr : public Stmt
{
public:
    virtual void handle(Handler * handler) {
        handler->handleExpr(this);
    }
public:
    Expr(yyltype loc) : Stmt(loc) {}
    Expr() : Stmt() {}
};
/* This node type is used for those places where an expression is optional.
* We could use a NULL pointer, but then it adds a lot of checking for
* NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleEmptyExpr(this);
    }
public:
};
class IntConstant : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleIntConstant(this);
    }
    int value;
public:
    IntConstant(yyltype loc, int val);
};
class DoubleConstant : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleDoubleConstant(this);
    }
    double value;
public:
    DoubleConstant(yyltype loc, double val);
};
class BoolConstant : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleBoolConstant(this);
    }
    bool value;
public:
    BoolConstant(yyltype loc, bool val);
};
class StringConstant : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleStringConstant(this);
    }
    char *value;
public:
    StringConstant(yyltype loc, const char *val);
};
class NullConstant : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleNullConstant(this);
    }
public:
    NullConstant(yyltype loc) : Expr(loc) {}
};
class Operator : public Node
{
public:
    virtual void handle(Handler * handler) {
        handler->handleOperator(this);
    }
    char tokenString[4];
public:
    Operator(yyltype loc, const char *tok);
    friend ostream& operator<<(ostream& out, Operator *o) {
        return out << o->tokenString;
    }
};
class CompoundExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleCompoundExpr(this);
    }
    Operator *op;
    Expr *left, *right; // left will be NULL if unary
public:
    CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
    CompoundExpr(Operator *op, Expr *rhs);             // for unary
};
class ArithmeticExpr : public CompoundExpr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleArithmeticExpr(this);
    }
public:
    ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
};
class RelationalExpr : public CompoundExpr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleRelationalExpr(this);
    }
public:
    RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
};
class EqualityExpr : public CompoundExpr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleEqualityExpr(this);
    }
public:
    EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() {
        return "EqualityExpr";
    }
};
class LogicalExpr : public CompoundExpr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleLogicalExpr(this);
    }
public:
    LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    const char *GetPrintNameForNode() {
        return "LogicalExpr";
    }
};
class AssignExpr : public CompoundExpr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleAssignExpr(this);
    }
public:
    AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() {
        return "AssignExpr";
    }
};
class LValue : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleLValue(this);
    }
public:
    LValue(yyltype loc) : Expr(loc) {}
};
class This : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleThis(this);
    }
public:
    This(yyltype loc) : Expr(loc) {}
};
class ArrayAccess : public LValue
{
public:
    virtual void handle(Handler * handler) {
        handler->handleArrayAccess(this);
    }
    Expr *base, *subscript;
public:
    ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
};
/* Note that field access is used both for qualified names
* base.field and just field without qualification. We don't
* know for sure whether there is an implicit "this." in
* front until later on, so we use one node type for either
* and sort it out later. */
class FieldAccess : public LValue
{
public:
    virtual void handle(Handler * handler) {
        handler->handleFieldAccess(this);
    }
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
public:
    FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
};
/* Like field access, call is used both for qualified base.field()
* and unqualified field().  We won't figure out until later
* whether we need implicit "this." so we use one node type for either
* and sort it out later. */
class Call : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleCall(this);
    }
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    List<Expr*> *actuals;
public:
    Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
};
class NewExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleNewExpr(this);
    }
    NamedType *cType;
public:
    NewExpr(yyltype loc, NamedType *clsType);
};
class NewArrayExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleNewArrayExpr(this);
    }
    Expr *size;
    Type *elemType;
public:
    NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
};
class ReadIntegerExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleReadIntegerExpr(this);
    }
public:
    ReadIntegerExpr(yyltype loc) : Expr(loc) {}
};
class ReadLineExpr : public Expr
{
public:
    virtual void handle(Handler * handler) {
        handler->handleReadLineExpr(this);
    }
public:
    ReadLineExpr(yyltype loc) : Expr (loc) {}
};
#endif
