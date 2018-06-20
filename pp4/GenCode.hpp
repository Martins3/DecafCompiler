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
#include "./utility.h"

#include "./tac.h"
#include "./codegen.h"
#include "./BuildSymbol.hpp"
#include "./FnLabel.hpp"

#include <iostream>
#include <cstdio>
#include <stack>
#include <deque>
#include <map>

/**
 * XXX: 想知道, class 只可以new 吗？
 * 变量的位置：
 *      1. 如果是local sp + offset
 *      2. 如果是global gp + offset 的处理
 *      3. 成员变量， 全部使用Location 分装， 如果是this, 那么特殊处理
 */

class  GenCode: public Handler{
public:

    static GenCode * G;
    static Type * exprType; // 设置为静态， 为了让GetType和GenCode公用
    static deque<Hashtable<VarDecl *> * > * nameScope; // 获取局部变量　成员变量　和　全局变量的VarDecl
    static Hashtable<Decl *> * globalDecl;
    static ClassDecl * curClass; // 方便this的访问

    CodeGenerator * codeGenerator;
    Location * returnLoc; // 计算出来返回值的结果
    bool storeLValue;
    deque<Hashtable<Location *> * > scope; // 为了获取heap 和 stack 变量的位置的索引





    Hashtable<int> memOffset; // 进入class 中间之后，访问class 变量返回位置 ???
    stack<const char*> * gBreakLabels;
    Location * assignLocPara;


    GenCode();
    void handleClassMember(ClassDecl * c); // 预处理class为函数和变量访问打下基础
    Location * getMemLoc(const char * name);
    void handleCalculateExpr(CompoundExpr * a);
    Decl * getGlobalDecl(const char * name);

    FnDecl * getMemberFn(ClassDecl * c, const char * name);
    VarDecl * getMemberVar(ClassDecl * c, const char * name);

    VarDecl * getNameVar(const char * name); // 获取使用的对象的类型
    bool isSysCall(Call *);
    FnDecl * getFnDeclByCall(Call *);


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

class GetType : public GenCode{
public:
    static GetType * T;

    void handleEmptyExpr(EmptyExpr * e);

    void handleIntConstant(IntConstant * i);
    void handleDoubleConstant(DoubleConstant * d);
    void handleBoolConstant(BoolConstant * b);
    void handleStringConstant(StringConstant * s);
    void handleNullConstant(NullConstant * n);

    void handleArithmeticExpr(ArithmeticExpr * a);
    void handleRelationalExpr(RelationalExpr * r);
    void handleEqualityExpr(EqualityExpr * e);
    void handleLogicalExpr(LogicalExpr * l);
    void handleAssignExpr(AssignExpr * a);
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
