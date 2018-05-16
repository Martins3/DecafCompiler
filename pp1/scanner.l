/* File:  scanner.l
 * ----------------
 * Lex input file to generate the scanner for the compiler.
 */

%{

/* The text within this first region delimited by %{ and %} is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */

#include <string.h>
#include "scanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"

/* Global variable: yylval
 * -----------------------
 * This global variable is how we get attribute information about the token
 * just scanned to the client. The scanner sets the global variable
 * appropriately and since it's global the client can just read it.  In the
 * future, this variable will be declared for us in the y.tab.c file
 * produced by Yacc, but for now, we declare it manually.
 */
YYSTYPE yylval;  // manually declared for pp1, later Yacc provides

/* Global variable: yylloc
 * -----------------------
 * This global variable is how we get position information about the token
 * just scanned to the client. (Operates similarly to yylval above)
 */
struct yyltype yylloc; // manually dclared for pp1, later Yacc provides


/* Macro: YY_USER_ACTION
 * ---------------------
 * This flex built-in macro can be defined to provide an action which is
 * always executed prior to any matched rule's action. Basically, it is
 * a way of having a piece of code common to all actions factored out to
 * this routine.  We already defined it for you and left the empty
 * function DoBeforeEachAction ready for your use as needed. It will
 * be called once for each pattern scanned from the file, before
 * executing its action.
 */
static void DoBeforeEachAction();
#define YY_USER_ACTION DoBeforeEachAction();

%}

 /* The section before the first %% is the Definitions section of the lex
  * input file. Here is where you set options for the scanner, define lex
  * states, and can set up definitions to give names to regular expressions
  * as a simple substitution mechanism that allows for more readable
  * entries in the Rules section later.

  "T_Void", "T_Int", "T_Double", "T_Bool", "T_String", "T_Class", "T_Null", "T_Dims",
  "T_LessEqual", "T_GreaterEqual", "T_Equal", "T_NotEqual",
  "T_And", "T_Or", "T_While", "T_For", "T_If", "T_Else", "T_Return",
  "T_Break", "T_Extends", "T_This", "T_Implements", "T_Interface",
  "T_New", "T_NewArray","T_Identifier", "T_StringConstant",
  "T_IntConstant", "T_DoubleConstant", "T_BoolConstant", "T_Print",
  "T_ReadInteger", "T_ReadLine"

    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1];
  */

 /* regex definitions */
space [\ ]
tab [\t]
newline [\r]?[\n]

letter [a-zA-Z]
digit [0-9]
hexDigit [0-9a-fA-f]
id {letter}({letter}|{digit}|_)*
number {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
exp	([Ee][-+]?[0-9]+)

 /* BEGIN RULES SECTION */
%%
true { yylval.boolConstant = true; return T_BoolConstant;}
false { yylval.boolConstant = false; return T_BoolConstant;}

([0-9]+) {yylval.integerConstant = strtol(yytext, NULL, 10); return T_IntConstant;}
0(x|X)([0-9a-fA-F]+) {yylval.integerConstant = strtol(yytext, NULL, 16); return T_IntConstant;}
[0-9]+"."[0-9]*{exp}? { yylval.doubleConstant = strtod(yytext, NULL); return T_DoubleConstant;}

"\""[^\n^\"]*"\"" {yylval.stringConstant = yytext; return T_StringConstant;}
"\""[^\^\n"]*$ {
    yylval.stringConstant = yytext;
    ReportError::UntermString(&yylloc, yytext);
    }

"/*"([^*]|\*+[^*/])*\*+"/" {}
"//"[^\n]*$  {}


"void"           {return T_Void;}
"int"            {return T_Int;}
"double"         {return T_Double;}
"bool"           {return T_Bool;}
"string"         {return T_String;}
"class"          {return T_Class;}
"interface"      {return T_Interface;}
"null"           {return T_Null;}
"this"           {return T_This;}
"extends"        {return T_Extends;}
"implements"     {return T_Implements;}
"for"            {return T_For;}
"while"          {return T_While;}
"if"             {return T_If;}
"else"           {return T_Else;}
"return"         {return T_Return;}
"break"          {return T_Break;}
"new"            {return T_New;}
"NewArray"       {return T_NewArray;}
"Print"          {return T_Print;}
"ReadInteger"    {return T_ReadInteger;}
"ReadLine"       {return T_ReadLine;}
"+"    {return '+';}
"-"    {return '-';}
"*"    {return '*';}
"/"    {return '/';}
"%"    {return '%';}
"<"    {return '<';}
"<="   {return T_LessEqual;}
">"    {return '>';}
">="   {return T_GreaterEqual;}
"="    {return '=';}
"=="   {return T_Equal;}
"!="   {return T_NotEqual;}
"&&"   {return T_And;}
"||"   {return T_Or;}
"!"    {return '!';}
";"    {return ';';}
","    {return ',';}
"."    {return '.';}
"[]"   {return T_NewArray;}
"["    {return '[';}
"]"    {return ']';}
"("    {return '(';}
")"    {return ')';}
"{"    {return '{';}
"}"    {return '}';}

{id} {
    if(strlen(yytext) > 31){
        ReportError::LongIdentifier(&yylloc, yytext);
        memset(yylval.identifier, 0, sizeof(char) * 32);
    }
    strncpy(yylval.identifier, yytext, 31);
    return T_Identifier;
    }

{space} {}
{tab} {}
{newline} {}


. {ReportError::UnrecogChar(&yylloc, *yytext); }
%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated lex.yy.c file.
 * This section is where you put definitions of helper functions.
 */


/* Function: InitScanner
 * ---------------------
 * This function will be called before any calls to yylex().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the scanner (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yy_flex_debug that controls whether flex prints debugging information
 * about each token and what rule was matched. If set to false, no information
 * is printed. Setting it to true will give you a running trail that might
 * be helpful when debugging your scanner. Please be sure the variable is
 * set to false when submitting your final version.
 */
void InitScanner()
{
    PrintDebug("lex", "Initializing scanner");
    yy_flex_debug = false;

    yylloc.first_line = 1;
    yylloc.first_column = 0;
    yylloc.last_line = 1;
    yylloc.last_column = 0;
}


/* Function: DoBeforeEachAction()
 * ------------------------------
 * This function is installed as the YY_USER_ACTION. This is a place
 * to group code common to all actions.
 */
static void DoBeforeEachAction()
{

    // 分析当前
    int line_inc = 0;
    int column_index = 0;
    unsigned index = 0;
    while(yytext[index] != '\0'){
        if(yytext[index] == '\n'){
            line_inc ++;
            column_index = -1;
        }
        if(yytext[index] == '\t') column_index += 7;
        column_index ++;
        index ++;
    }

    // 检查到当前含有换行符, 只会是newline　comment unterminated_string
    if(line_inc > 0){
        yylloc.first_line += line_inc;
        yylloc.last_column = column_index;
    }else{
        yylloc.first_column = yylloc.last_column + 1;
        yylloc.last_column = yylloc.first_column + column_index - 1;
    }

}
