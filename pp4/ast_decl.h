/* File: ast_decl.h
* ----------------
* In our parse tree, Decl nodes are used to represent and
* manage declarations. There are 4 subclasses of the base class,
* specialized for declarations of variables, functions, classes,
* and interfaces.
*
* pp3: You will need to extend the Decl classes to implement
* semantic processing including detection of declaration conflicts
* and managing scoping issues.
*/
#ifndef _H_ast_decl
#define _H_ast_decl
#include "ast.h"
#include "list.h"
class Decl : public Node
{
public:
    virtual void handle(Handler * handler) {
        handler->handleDecl(this);
    }
    Identifier *id;
public:
    Decl(Identifier *name);
    friend ostream& operator<<(ostream& out, Decl *d) {
        return out << d->id;
    }
};
class VarDecl : public Decl
{
public:
    virtual void handle(Handler * handler) {
        handler->handleVarDecl(this);
    }
    Type *type;
public:
    VarDecl(Identifier *name, Type *type);
};
class ClassDecl : public Decl
{
public:
    virtual void handle(Handler * handler) {
        handler->handleClassDecl(this);
    }
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;
public:
    ClassDecl(Identifier *name, NamedType *extends,
              List<NamedType*> *implements, List<Decl*> *members);
};
class InterfaceDecl : public Decl
{
public:
    virtual void handle(Handler * handler) {
        handler->handleInterfaceDecl(this);
    }
    List<Decl*> *members;
public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
};
class FnDecl : public Decl
{
public:
    virtual void handle(Handler * handler) {
        handler->handleFnDecl(this);
    }
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
};
#endif
