
%{

/* The text within this first region delimited by %{ and %} is assumed to
 * be C/C++ code and will be copied verbatim to the lex.yy.c file ahead
 * of the definitions of the yylex() function. Add other header file inclusions
 * or C++ variable declarations/prototypes that are needed by your code here.
 */

#include <string.h>
#include <iostream>
#include <vector>

#include "scanner.h"
#include "utility.h" // for PrintDebug()
#include "errors.h"
#include "parser.h"

static vector<string> document;
static void DoBeforeEachAction();
#define YY_USER_ACTION DoBeforeEachAction();

%}

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



void InitScanner()
{
    PrintDebug("lex", "Initializing scanner");
    yy_flex_debug = false;

    yylloc.first_line = 1;
    yylloc.first_column = 0;
    yylloc.last_line = 1;
    yylloc.last_column = 0;

    string line;
    while(getline(cin, line)){
        document.push_back(line);
    }
    rewind(stdin);
}


/* Function: DoBeforeEachAction()
 * ------------------------------
 * This function is installed as the YY_USER_ACTION. This is a place
 * to group code common to all actions.
 */
static void DoBeforeEachAction()
{



    // 分析当前

    // 如果token中间含有换行符
    // 如果没有含有任何换行符
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

const char *GetLineNumbered(int n){
    if(n < 0) return NULL;
    if(n + 1 > document.size()) return NULL;
    return document[n - 1].c_str();
}
