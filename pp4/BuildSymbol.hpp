#ifndef BUILD_SYSBOL_H
#define BUILD_SYSBOL_H

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

class  BuildSymbol: public Handler{
public:

    static BuildSymbol * B;

    BuildSymbol(){
        returnType = NULL;
        inClass = false;
        loopLevel = 0;
        exprType = Type::errorType;
        handleNamedTypePara = reasonT::LookingForType;
    }

    // todo:创建从开作用域中间制定类型的系列方法
    reasonT handleNamedTypePara;

    deque<Hashtable<Decl*> *> scope;
    Hashtable<Hashtable<Decl*> *> memberDecls; // 用于收集所有class的member，同时分析继承问题
    Type * returnType; // 函数不可以嵌套
    bool inClass; //　确定是否可以使用this this的可用列表必定在最后第二个
    int loopLevel; // 用于判断当前是否含有break
    Type * exprType; // 用于expr 分析结束之后　返回表达式类型
    Identifier * curClass; // 辅助this获取类型

    stack<const char *> * getSuperClass(const char * className);
    bool isBaseType(Type * t);
    Hashtable<Decl*> * checkDeclConflict(List<Decl*> * declList);
    Hashtable<Decl*> * checkDeclConflict(List<VarDecl*> * declList);
    bool CheckIdentifierNotDeclared(Identifier * id, reasonT whyNeeded);
    bool isTypeEqual(Type * src, Type * dest);
    bool isTypeCompatiable(Type * left, Type * right);

    Hashtable<Decl*> * checkClass(ClassDecl * d);
    Hashtable<Decl*> * checkInterface(InterfaceDecl * in);

    bool checkMisMatch(List<VarDecl*> * superPara, List<VarDecl *> * childPara);
    bool checkMisMatch(Identifier * id, FnDecl * fn, List<Expr *> * arguments);
    Decl * checkOpenScope(const char * name);


    // discard
    void addDecl(Decl * v);


    // debug
    void print_hashtables();

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
