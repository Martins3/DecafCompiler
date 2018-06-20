#ifndef GET_TYPE_H
#define GET_TYPE_H

#include "./GenCode.hpp"
#include "./list.h"
#include "./hashtable.hpp"
#include "./ast.h"
#include "./ast_stmt.h"
#include "./ast_decl.h"
#include "./ast_expr.h"
#include "./ast_type.h"
#include "./errors.h"
#include "hashtable.hpp"

class GetType : public GenCode{
public:
    static GetType * T;
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
};
#endif
