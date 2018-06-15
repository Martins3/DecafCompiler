%{
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"
#include "BuildSymbol.hpp"
void yyerror(const char *msg); // standard error-handling routine
%}
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null

    Decl *decl;
    List<Decl*> *       declList;
    EmptyExpr *         emptyExpr;
    VarDecl *           varDecl;

    /* token包装类 */
    IntConstant *       classIntConstant;
    DoubleConstant *    classDoubleConstant;
    StringConstant *    classStringConstant;
    BoolConstant *      classBoolConstant;
    NullConstant *      classNullConstant;
    Identifier *        classIdentifier;

    /* +,对应list */
    List<VarDecl*> *    varDeclList;
    List<NamedType*> *  namedTypeList;
    NamedType *         namedType;
    Expr *              expr;
    List<Expr*> *       exprList;

    /* *对应的list */
    List<Stmt*> *       stmtList;
    List<FnDecl*> *     fnDeclList;
    FnDecl  * fnDecl;

    /* 添加类型 */
    Program *           program;
    InterfaceDecl *     interfaceDecl;
    BreakStmt *         breakStmt;
    ForStmt *           forStmt;
    ReturnStmt *        returnStmt;
    IfStmt *            ifStmt;
    PrintStmt *         printStmt;
    StmtBlock *         stmtBlock;
    WhileStmt *         whileStmt;
    Stmt *              stmt;
    /* LoopStmt *          loopStmt; */
    /* ConditionalStmt *   conditionalStmt; */
    LValue *            lvalue;
    Call *              call;
    ClassDecl *         classDecl;

    Type *              type;
}


%token   T_Void T_Bool T_Int T_Double T_String T_Class
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
%token  <identifier> T_Identifier
%token  <stringConstant> T_StringConstant
%token  <integerConstant> T_IntConstant
%token  <doubleConstant> T_DoubleConstant
%token  <boolConstant> T_BoolConstant


%type <declList>        DeclList
%type <decl>            Decl
%type <emptyExpr>       EmptyExpr
%type <varDecl>         VariableDecl
%type <varDecl>         Variable
%type <classStringConstant>  stringConstant
%type <classIntConstant>     intConstant
%type <classBoolConstant>    boolConstant
%type <classDoubleConstant>  doubleConstant
%type <classNullConstant>    nullConstant
%type <classIdentifier>      ident

%type <expr>            Expr
%type <exprList>        ExprList
%type <varDeclList>     VariableDeclList
%type <namedTypeList>   NamedTypeList
%type <namedType>       NamedType

%type <fnDecl>          Prototype
%type <fnDecl>          FunctionDecl
%type <declList>        PrototypeList
%type <stmtList>        StmtList

%type <decl>            Field
%type <declList>        FieldList

%type <program>         Program
%type <type>            Type
%type <varDeclList>     Formals
%type <interfaceDecl>   InterfaceDecl

%type   <breakStmt>     BreakStmt
%type   <forStmt>       ForStmt
%type   <returnStmt>    ReturnStmt
%type   <ifStmt>        IfStmt
%type   <printStmt>     PrintStmt
%type   <stmtBlock>     StmtBlock
%type   <whileStmt>     WhileStmt
%type   <stmt>          Stmt
/* %type   <loopStmt>      LoopStmt */
/* %type   <conditionalStmt> ConditionalStmt */
%type   <lvalue>        LValue
%type   <call>          Call
%type   <expr>          Constant
%type   <exprList>      Actuals
/* %type   <intConstant>   Subtraction */
/* %type   <intConstant>   Minus */

%type  <classDecl>      ClassDecl
%type  <varDeclList>    VariableList

%nonassoc '='
%left T_Or
%left T_And
%nonassoc T_Equal T_NotEqual
%nonassoc '<' T_LessEqual '>' T_GreaterEqual
%left '+' '-'
%left '*' '/' '%'
%nonassoc '!' UMINUS
%nonassoc '[' '.'
%nonassoc  T_Lower_Than_Else
%nonassoc  T_Else

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
 */

Program         :   DeclList    {
        @1;
        /* pp2: The @1 is needed to convince
        * yacc to set up yylloc. You can remove
        * it once you have other uses of @n*/
        Program *program = new Program($1);
        // if no errors, advance to next phase
        if (ReportError::NumErrors() == 0){
            program->handle(BuildSymbol::B);
        }
                }
                ;

DeclList        :   DeclList Decl       {($$ = $1)->Append($2);}
                |   Decl                {($$ = new List<Decl*>)->Append($1);}
                ;

Decl            :   VariableDecl        { $$ = $1;}
                |   FunctionDecl        { $$ = $1;}
                |   ClassDecl           { $$ = $1;}
                |   InterfaceDecl       { $$ = $1;}
                ;

VariableDecl    :   Variable ';'        {$$ = $1;}
                ;


    /* VarDecl(Identifier *name, Type *type); */
Variable        :   Type ident          {$$ = new VarDecl($2, $1);}
                ;

Type            :   T_Int               {$$ = Type::intType;}
                |   T_Double            {$$ = Type::doubleType;}
                |   T_Bool              {$$ = Type::boolType;}
                |   T_String            {$$ = Type::stringType;}
                |   ident               {$$ = new NamedType($1);}
                |   Type T_NewArray     {$$ = new ArrayType(Join(@1, @2), $1); }
                ;

    /* FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals); */
    /* void FnDecl::SetFunctionBody(Stmt *b) { */
FunctionDecl    :   Type ident '(' Formals ')' StmtBlock    {
                    $$ = new FnDecl($2, $1, $4);
                    $$-> SetFunctionBody($6);
                    }
                |   T_Void ident '(' Formals ')' StmtBlock    {
                    $$ = new FnDecl($2, Type::voidType, $4);
                    $$-> SetFunctionBody($6);
                    }
                ;

Formals         :   VariableList         {$$ = $1;}
                |   /* none */           {$$ = new List<VarDecl*>();}
                ;

    /* ClassDecl(Identifier *name, NamedType *extends,
               List<NamedType*> *implements, List<Decl*> *members);
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    */

ClassDecl       :   T_Class ident '{' FieldList '}'    {
                    $$ = new ClassDecl($2, NULL, new List<NamedType*>(), $4 );
                    }
                |   T_Class ident '{'  '}'    {
                    $$ = new ClassDecl($2, NULL, new List<NamedType*>(),  new List<Decl*>());
                    }
                |   T_Class ident T_Implements NamedTypeList '{' FieldList '}'    {
                    $$ = new ClassDecl($2, NULL, $4, $6 );
                    }
                |   T_Class ident T_Implements NamedTypeList '{'  '}'    {
                    $$ = new ClassDecl($2, NULL, $4, new List<Decl*>() );
                    }
                |   T_Class ident T_Extends NamedType '{' FieldList '}'    {
                    $$ = new ClassDecl($2, $4, new List<NamedType*>(), $6 );
                    }
                |   T_Class ident T_Extends NamedType '{'  '}'    {
                    $$ = new ClassDecl($2, $4, new List<NamedType*>(), new List<Decl*>());
                    }
                |   T_Class ident T_Extends NamedType T_Implements NamedTypeList '{' FieldList '}'    {
                    $$ = new ClassDecl($2, $4, $6, $8 );
                    }
                |   T_Class ident T_Extends NamedType T_Implements NamedTypeList '{'  '}'    {
                    $$ = new ClassDecl($2, $4, $6, new List<Decl*>()  );
                    }
                ;

Field           :   VariableDecl        {$$ = $1;}
                |   FunctionDecl        {$$ = $1;}
                ;


    /* InterfaceDecl(Identifier *name, List<Decl*> *members); */
InterfaceDecl   :   T_Interface ident '{' PrototypeList '}'    {
                    $$ = new InterfaceDecl($2, $4);
                }
                |   T_Interface ident '{'  '}'    {
                    $$ = new InterfaceDecl($2, new List<Decl*>());
                }
                ;

Prototype       :   Type ident '(' Formals ')' ';'    {$$ = new FnDecl($2, $1, $4);}
                |   T_Void ident '(' Formals ')' ';'    {
                    $$ = new FnDecl($2, Type::voidType, $4);
                    }
                ;

    /* StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements); */
StmtBlock       :   '{'  '}'    {
                    $$ = new StmtBlock(new List<VarDecl*>(), new List<Stmt*>() );
                    }
                |   '{' StmtList '}'    {
                    $$ = new StmtBlock(new List<VarDecl*>(), $2 );
                    }
                |   '{' VariableDeclList '}'    {
                    $$ = new StmtBlock($2, new List<Stmt*>() );
                    }
                |   '{' VariableDeclList StmtList '}'    {
                    $$ = new StmtBlock($2, $3);
                    }
                ;

Stmt            :   EmptyExpr ';'       {$$ = $1;}
                |   Expr ';'            {$$ = $1;}
                |   IfStmt              {$$ = $1;}
                |   WhileStmt           {$$ = $1;}
                |   ForStmt             {$$ = $1;}
                |   BreakStmt           {$$ = $1;}
                |   ReturnStmt          {$$ = $1;}
                |   PrintStmt           {$$ = $1;}
                |   StmtBlock           {$$ = $1;}
                ;

    /* IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody); */
IfStmt          :   T_If '(' Expr ')' Stmt T_Else Stmt    {
                    $$ = new IfStmt($3, $5, $7);
                    }
                |   T_If '(' Expr ')' Stmt %prec T_Lower_Than_Else  {
                    $$ = new IfStmt($3, $5, NULL);
                    }
                ;

    /* WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {} */
WhileStmt       :   T_While '(' Expr ')' Stmt    {$$ = new WhileStmt($3, $5);}
                ;

    /* ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body); */
ForStmt         :   T_For '('  Expr ';' Expr ';' Expr ')' Stmt    {
                    $$ = new ForStmt($3, $5, $7, $9);
                    }
                |   T_For '('  Expr ';' Expr ';' EmptyExpr ')' Stmt    {
                    $$ = new ForStmt($3, $5, $7, $9);
                    }
                |   T_For '('  EmptyExpr ';' Expr ';' Expr ')' Stmt    {
                    $$ = new ForStmt($3, $5, $7, $9);
                    }
                |   T_For '('  EmptyExpr ';' Expr ';' EmptyExpr ')' Stmt    {
                    $$ = new ForStmt($3, $5, $7, $9);
                    }
                ;

/* returnstmt(yyltype loc, expr *expr); */
ReturnStmt      :   T_Return Expr ';'    {$$ = new ReturnStmt(@2, $2);}
                |   T_Return EmptyExpr ';'    {$$ = new ReturnStmt(@2, $2);}

                ;
    /* BreakStmt(yyltype loc) : Stmt(loc) {} */
BreakStmt       :   T_Break ';'         {$$ =  new BreakStmt(@1);}
                ;

    /* PrintStmt(List<Expr*> *arguments); */
PrintStmt       :   T_Print '(' ExprList ')' ';'    {$$ = new PrintStmt($3); }
                ;

Call            :   ident '(' Actuals ')'    {
                    $$ = new Call(Join(@1, @4), NULL, $1, $3);
                    }
                |   Expr '.' ident '(' Actuals ')'    {
                    $$ = new Call(Join(@1, @4), $1, $3, $5);
                    }
                ;


LValue          :   ident               {$$ = new FieldAccess(NULL, $1);}
                |   Expr '.' ident      {$$ = new FieldAccess($1, $3);}
                |   Expr '[' Expr ']'    {$$ = new ArrayAccess(Join(@1, @4), $1, $3);}
                ;

Expr            :   LValue '=' Expr     {
                    Operator * op = new Operator(@2, "=");
                    $$ = new AssignExpr($1, op, $3);
                    }
                |   Constant            { $$ = $1;}
                |   LValue              { $$ = $1;}
                |   T_This              { $$ = new This(@1);}
                |   Call                { $$ = $1;}
                |   '(' Expr ')'        { $$ = $2;}
                |   Expr '+' Expr       {
                    Operator * op = new Operator(@2, "+");
                    $$ = new ArithmeticExpr($1, op, $3);
                    }
                |   Expr '-' Expr       {
                    Operator * op = new Operator(@2, "-");
                    $$ = new ArithmeticExpr($1, op, $3);
                    }
                |   Expr '*' Expr       {
                    Operator * op = new Operator(@2, "*");
                    $$ = new ArithmeticExpr($1, op, $3);
                    }
                |   Expr '/' Expr       {
                    Operator * op = new Operator(@2, "/");
                    $$ = new ArithmeticExpr($1, op, $3);
                    }
                |   Expr '%' Expr       {
                    Operator * op = new Operator(@2, "%");
                    $$ = new ArithmeticExpr($1, op, $3);
                    }
                |   '-' Expr %prec UMINUS {
                    Operator * op = new Operator(@1,  "-");
                    $$ = new ArithmeticExpr(op, $2);
                    }
                |   Expr '<' Expr       {
                    Operator * op = new Operator(@2, "<");
                    $$ = new RelationalExpr($1, op, $3);
                    }
                |   Expr T_LessEqual Expr    {
                    Operator * op = new Operator(@2, "<=");
                    $$ = new RelationalExpr($1, op, $3);
                    }
                |   Expr '>' Expr       {
                    Operator * op = new Operator(@2, ">");
                    $$ = new RelationalExpr($1, op, $3);
                    }
                |   Expr T_GreaterEqual Expr    {
                    Operator * op = new Operator(@2, ">=");
                    $$ = new RelationalExpr($1, op, $3);
                    }
                |   Expr T_Equal Expr    {
                    Operator * op = new Operator(@2, "==");
                    $$ = new EqualityExpr($1, op, $3);
                    }
                |   Expr T_NotEqual Expr    {
                    Operator * op = new Operator(@2, "!=");
                    $$ = new EqualityExpr($1, op, $3);
                    }
                |   Expr T_And Expr     {
                    Operator * op = new Operator(@2, "&&");
                    $$ = new LogicalExpr($1, op, $3);
                    }
                |   Expr T_Or Expr      {
                    Operator * op = new Operator(@2, "||");
                    $$ = new LogicalExpr($1, op, $3);
                    }
                |   '!' Expr            {
                    Operator * op = new Operator(@1, "!");
                    $$ = new LogicalExpr(op, $2);
                    }
                |   T_ReadInteger '(' ')'    { $$ = new ReadIntegerExpr(Join(@1, @3));}
                |   T_ReadLine '(' ')'    { $$ = new ReadLineExpr(Join(@1, @3));}
                |   T_New NamedType        {$$ = new NewExpr(Join(@1, @2), $2);}
                |   T_NewArray '(' Expr ',' Type ')'    {$$ = new
                NewArrayExpr(Join(@1, @6), $3, $5);}
                ;



Actuals         :   ExprList           {$$ = $1;}
                |    /*none*/          {$$ = new List<Expr*>();}
                ;

Constant        :   intConstant         {$$ = $1;}
                |   doubleConstant      {$$ = $1;}
                |   boolConstant        {$$ = $1;}
                |   stringConstant      {$$ = $1;}
                |   nullConstant        {$$ = $1;}
                ;

intConstant     :   T_IntConstant       {$$ = new IntConstant(@1, $1);}
                ;

doubleConstant  :   T_DoubleConstant    {$$ = new DoubleConstant(@1, $1);}
                ;

boolConstant    :   T_BoolConstant      {$$ = new BoolConstant(@1, $1);}
                ;

stringConstant  :   T_StringConstant    {$$ = new StringConstant(@1, $1);}
                ;

nullConstant    :   T_Null              {$$ = new NullConstant(@1);}
                ;

ident           :   T_Identifier        {$$ = new Identifier(@1, $1);}
                ;

ExprList        :   Expr                {($$ = new List<Expr*>())->Append($1);}
                |   ExprList ',' Expr   {($$ = $1)->Append($3);}
                ;

VariableList    :   Variable                 {($$ = new List<VarDecl*>())->Append($1);}
                |   VariableList ',' Variable     {($$ = $1)->Append($3);}
                ;

NamedTypeList    :   NamedType               {($$ = new List<NamedType*>())->Append($1);}
                |   NamedTypeList ',' NamedType {($$ = $1)->Append($3);}
                ;

NamedType       :   ident               {$$ = new NamedType($1);}
                ;

PrototypeList   :   Prototype           {($$ = new List<Decl*>())->Append($1);}
                |   PrototypeList   Prototype {($$ = $1)->Append($2);}
                ;

StmtList        :   Stmt                {($$ = new List<Stmt*>())->Append($1);}
                |   StmtList Stmt       {($$ = $1)->Append($2);}
                ;

FieldList       :   Field               {($$ = new List<Decl*>())->Append($1);}
                |   FieldList Field     {($$ = $1)->Append($2);}
                ;

VariableDeclList:   VariableDecl        {($$ = new List<VarDecl*>())->Append($1);}
                |   VariableDeclList VariableDecl {($$ = $1)->Append($2);}
                ;

EmptyExpr       : /* none */            {$$ = new EmptyExpr();}
                ;

%%

void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
