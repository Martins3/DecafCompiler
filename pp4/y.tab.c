/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"
#include "BuildSymbol.hpp"
#include "GenCode.hpp"
void yyerror(const char *msg); // standard error-handling routine

#line 75 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Void = 258,
    T_Bool = 259,
    T_Int = 260,
    T_Double = 261,
    T_String = 262,
    T_Class = 263,
    T_LessEqual = 264,
    T_GreaterEqual = 265,
    T_Equal = 266,
    T_NotEqual = 267,
    T_Dims = 268,
    T_And = 269,
    T_Or = 270,
    T_Null = 271,
    T_Extends = 272,
    T_This = 273,
    T_Interface = 274,
    T_Implements = 275,
    T_While = 276,
    T_For = 277,
    T_If = 278,
    T_Else = 279,
    T_Return = 280,
    T_Break = 281,
    T_New = 282,
    T_NewArray = 283,
    T_Print = 284,
    T_ReadInteger = 285,
    T_ReadLine = 286,
    T_Identifier = 287,
    T_StringConstant = 288,
    T_IntConstant = 289,
    T_DoubleConstant = 290,
    T_BoolConstant = 291,
    UMINUS = 292,
    T_Lower_Than_Else = 293
  };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Identifier 287
#define T_StringConstant 288
#define T_IntConstant 289
#define T_DoubleConstant 290
#define T_BoolConstant 291
#define UMINUS 292
#define T_Lower_Than_Else 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 9 "parser.y" /* yacc.c:355  */

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

#line 243 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 274 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   919

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      51,    52,    42,    40,    56,    41,    48,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    50,
      38,    37,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    46,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   144,   144,   162,   163,   166,   167,   168,   169,   172,
     177,   180,   181,   182,   183,   184,   185,   190,   194,   200,
     201,   209,   212,   215,   218,   221,   224,   227,   230,   235,
     236,   241,   244,   249,   250,   256,   259,   262,   265,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   282,   285,
     291,   295,   298,   301,   304,   310,   311,   315,   319,   322,
     325,   331,   332,   333,   336,   340,   341,   342,   343,   344,
     345,   349,   353,   357,   361,   365,   369,   373,   377,   381,
     385,   389,   393,   397,   401,   405,   406,   407,   408,   414,
     415,   418,   419,   420,   421,   422,   425,   428,   431,   434,
     437,   440,   443,   444,   447,   448,   451,   452,   455,   458,
     459,   462,   463,   466,   467,   470,   471,   474
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "'='", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "UMINUS", "'['", "'.'", "T_Lower_Than_Else",
  "';'", "'('", "')'", "'{'", "'}'", "']'", "','", "$accept", "Program",
  "DeclList", "Decl", "VariableDecl", "Variable", "Type", "FunctionDecl",
  "Formals", "ClassDecl", "Field", "InterfaceDecl", "Prototype",
  "StmtBlock", "Stmt", "IfStmt", "WhileStmt", "ForStmt", "ReturnStmt",
  "BreakStmt", "PrintStmt", "Call", "LValue", "Expr", "Actuals",
  "Constant", "intConstant", "doubleConstant", "boolConstant",
  "stringConstant", "nullConstant", "ident", "ExprList", "VariableList",
  "NamedTypeList", "NamedType", "PrototypeList", "StmtList", "FieldList",
  "VariableDeclList", "EmptyExpr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    60,    62,
      43,    45,    42,    47,    37,    33,   292,    91,    46,   293,
      59,    40,    41,   123,   125,    93,    44
};
# endif

#define YYPACT_NINF -65

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-65)))

#define YYTABLE_NINF -16

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-16)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      93,    17,   -65,   -65,   -65,   -65,    17,    17,   -65,     2,
      93,   -65,   -65,    20,    -8,   -65,   -65,   -65,   -65,    26,
       6,    29,   -65,   -65,   -65,   -65,    33,    82,    17,    17,
     104,   165,    82,   -65,    -8,    38,    39,   -65,    -9,   -31,
     -65,   -65,   -65,   -65,   -65,   170,    17,   -65,    -8,   -65,
     177,    52,   -65,    53,    82,    17,   189,   207,    17,   -65,
     -65,    54,    62,   -65,   -65,    53,   276,   -65,   -65,    25,
     -65,   222,   -65,   230,   -65,    82,    82,   -65,   -65,   -65,
      66,    75,    83,   868,   102,    17,   109,   110,   112,   113,
     -65,   -65,   -65,   -65,   868,   868,   868,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   116,   525,
     -65,   -65,   -65,   -65,   -65,   -65,    51,   772,   318,   117,
     241,   -65,   -65,   114,   126,   868,   868,   868,   567,   134,
     136,   -65,   -65,   868,   868,   146,   147,    16,    16,   386,
     868,   868,   868,   868,   868,   868,   868,   868,   868,   868,
     868,   868,   868,   868,   868,    17,   -65,   868,   -65,   -65,
     -65,   -65,   806,   -65,   -65,   246,   153,   154,   407,   580,
     158,   451,   -65,   -65,   346,   677,   -16,   -65,   -65,   -65,
     677,   724,   724,   699,   699,   739,   688,   724,   724,    85,
      85,    16,    16,    16,   365,   164,   168,   160,   -65,   -65,
     -65,   -65,   840,   868,   868,   840,    82,   172,   868,   -65,
     868,   -65,   -65,   622,   635,   199,   -10,   -65,   677,   178,
     868,   868,   840,   -65,   -65,   466,   180,   510,   186,   -65,
     840,   840,   840,   840,   -65,   -65,   -65,   -65
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    13,    11,    12,    14,     0,     0,   101,     0,
       2,     4,     5,     0,     0,     6,     7,     8,    15,     0,
       0,     0,     1,     3,     9,    16,    10,    20,     0,     0,
       0,     0,    20,   104,     0,     0,    19,   108,     0,     0,
     106,    22,    29,    30,   113,     0,     0,    32,     0,   109,
       0,     0,    10,     0,     0,     0,     0,     0,     0,    21,
     114,     0,     0,    31,   110,     0,   117,    18,   105,     0,
      26,     0,    24,     0,   107,    20,    20,    17,   100,    67,
       0,     0,     0,   117,     0,     0,     0,     0,     0,     0,
      99,    96,    97,    98,     0,     0,     0,    35,   115,    47,
     111,    41,    42,    43,    45,    44,    46,    68,    66,     0,
      65,    91,    92,    93,    94,    95,    61,   117,   117,     0,
       0,    25,    23,     0,     0,     0,   117,     0,     0,    61,
       0,    57,    87,     0,     0,     0,     0,    75,    84,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    90,    36,   112,
      37,   116,   117,    39,    28,     0,     0,     0,     0,     0,
       0,     0,    55,    56,     0,   102,     0,    85,    86,    69,
      64,    77,    79,    80,    81,    82,    83,    76,    78,    70,
      71,    72,    73,    74,     0,    62,     0,    89,    38,    27,
      34,    33,   117,     0,     0,   117,     0,     0,     0,    63,
      90,    59,    50,     0,     0,    49,     0,    58,   103,     0,
     117,   117,   117,    88,    60,     0,     0,     0,     0,    48,
     117,   117,   117,   117,    51,    52,    53,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   231,     3,    40,   -15,    37,   -23,   -65,
     -30,   -65,   190,   -32,   -43,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,    -3,    32,   -65,   -65,   -65,   -65,   -65,
     -65,     0,   121,   -65,   201,   -20,   -65,   139,   -52,   -65,
     -64
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    42,    13,    14,    43,    35,    16,
      44,    17,    49,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   196,   110,   111,   112,   113,   114,
     115,   129,   197,    36,    39,    40,    50,   117,    45,   118,
     119
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,    19,    22,    12,    71,    73,    20,    21,    38,    51,
      18,    55,    34,    12,    26,    60,    48,    34,    25,   130,
      25,    67,    57,    28,     8,    58,    29,    18,    37,    37,
      18,    18,    18,    77,    52,    48,   207,    15,    74,    34,
     208,    60,   223,    60,    56,    18,    61,    15,    62,     8,
      18,    34,   123,   124,    18,    37,    18,    18,    37,    30,
      34,    34,   170,   154,   155,   132,   116,    33,   165,    98,
      24,    18,    33,    18,   159,    18,    18,    27,   120,   -15,
     128,    58,    31,   -15,    32,    37,     2,     3,     4,     5,
      53,   137,   138,   139,    68,    54,     1,     2,     3,     4,
       5,     6,   157,    34,    65,    75,    66,     1,     2,     3,
       4,     5,     7,    76,     8,    33,    33,   125,   116,   159,
      18,   161,   168,   169,   171,     8,   126,   151,   152,   153,
     174,   175,   154,   155,   127,    60,     8,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   131,   140,   175,   195,   226,   228,    41,   212,
     133,   134,   215,   135,   136,    18,   166,   163,    46,     2,
       3,     4,     5,     1,     2,     3,     4,     5,   167,   229,
      46,     2,     3,     4,     5,   157,   173,   234,   235,   236,
     237,   216,     1,     2,     3,     4,     5,     8,   177,   178,
     213,   214,     8,   200,   201,   218,    18,   175,   204,     8,
       1,     2,     3,     4,     5,   210,   208,   225,   227,    47,
     211,     8,   217,   222,    59,     1,     2,     3,     4,     5,
     224,    63,   231,     1,     2,     3,     4,     5,   233,     8,
      64,    23,   219,    70,     1,     2,     3,     4,     5,     1,
       2,     3,     4,     5,     8,   176,    69,   162,     0,     0,
       0,    72,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,   121,     0,     8,     0,
       2,     3,     4,     5,   122,     0,     0,     0,     0,     0,
       0,     0,    78,     0,    79,   164,     0,    80,    81,    82,
     199,    83,    84,    85,    86,    87,    88,    89,     8,    90,
      91,    92,    93,     0,     0,     0,     0,    94,     0,     0,
       0,    95,     2,     3,     4,     5,     0,    96,     0,    66,
      97,     0,     0,     0,    78,     0,    79,     0,     0,    80,
      81,    82,     0,    83,    84,    85,    86,    87,    88,    89,
       8,    90,    91,    92,    93,   141,   142,   143,   144,    94,
     145,   146,     0,    95,     0,     0,     0,     0,     0,    96,
       0,    66,   160,     0,   141,   142,   143,   144,     0,   145,
     146,     0,     0,     0,   147,   148,   149,   150,   151,   152,
     153,     0,     0,   154,   155,   141,   142,   143,   144,     0,
     145,   146,   206,   147,   148,   149,   150,   151,   152,   153,
       0,     0,   154,   155,     0,     0,   141,   142,   143,   144,
     209,   145,   146,     0,   147,   148,   149,   150,   151,   152,
     153,     0,     0,   154,   155,     0,     0,     0,   179,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,     0,     0,   154,   155,     0,     0,     0,   202,
     141,   142,   143,   144,     0,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,   141,   142,   143,   144,     0,
     145,   146,     0,     0,     0,     0,     0,     0,     0,   147,
     148,   149,   150,   151,   152,   153,     0,     0,   154,   155,
       0,     0,     0,   205,   147,   148,   149,   150,   151,   152,
     153,     0,     0,   154,   155,     0,     0,     0,   230,   141,
     142,   143,   144,     0,   145,   146,     0,     0,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,     0,   145,
     146,     0,     0,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   153,     0,     0,   154,   155,     0,
       0,     0,   232,   147,   148,   149,   150,   151,   152,   153,
       0,     0,   154,   155,     0,   156,   141,   142,   143,   144,
       0,   145,   146,     0,     0,     0,     0,     0,     0,   141,
     142,   143,   144,     0,   145,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,     0,     0,   154,   155,     0,   172,   147,   148,
     149,   150,   151,   152,   153,     0,     0,   154,   155,     0,
     203,   141,   142,   143,   144,     0,   145,   146,     0,     0,
       0,     0,     0,     0,   141,   142,   143,   144,     0,   145,
     146,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   152,   153,     0,     0,   154,
     155,     0,   220,   147,   148,   149,   150,   151,   152,   153,
       0,     0,   154,   155,     0,   221,   141,   142,   143,   144,
       0,   145,   146,     0,     0,     0,     0,   141,   142,   143,
     144,     0,   145,     0,     0,     0,     0,     0,   141,   142,
     -16,   -16,     0,     0,     0,   147,   148,   149,   150,   151,
     152,   153,     0,     0,   154,   155,   147,   148,   149,   150,
     151,   152,   153,   -16,   -16,   154,   155,   147,   148,   149,
     150,   151,   152,   153,     0,     0,   154,   155,   141,   142,
     143,   144,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -16,   -16,   149,   150,   151,   152,   153,     0,
       0,   154,   155,     0,     0,     0,     0,   147,   148,   149,
     150,   151,   152,   153,     0,     0,   154,   155,    78,     0,
      79,     0,     0,    80,    81,    82,     0,    83,    84,    85,
      86,    87,    88,    89,     8,    90,    91,    92,    93,     0,
       0,     0,     0,    94,     0,     0,     0,    95,     0,     0,
       0,     0,    78,    96,    79,    66,   158,    80,    81,    82,
       0,    83,    84,    85,    86,    87,    88,    89,     8,    90,
      91,    92,    93,     0,     0,     0,     0,    94,     0,     0,
       0,    95,     0,     0,     0,     0,    78,    96,    79,    66,
     198,    80,    81,    82,     0,    83,    84,    85,    86,    87,
      88,    89,     8,    90,    91,    92,    93,     0,     0,     0,
       0,    94,     0,     0,    78,    95,    79,     0,     0,     0,
       0,    96,     0,    66,     0,    85,    86,     0,    88,    89,
       8,    90,    91,    92,    93,     0,     0,     0,     0,    94,
       0,     0,     0,    95,     0,     0,     0,     0,     0,    96
};

static const yytype_int16 yycheck[] =
{
       0,     1,     0,     0,    56,    57,     6,     7,    28,    32,
      10,    20,    27,    10,    14,    45,    31,    32,    28,    83,
      28,    53,    53,    17,    32,    56,    20,    27,    28,    29,
      30,    31,    32,    65,    34,    50,    52,     0,    58,    54,
      56,    71,    52,    73,    53,    45,    46,    10,    48,    32,
      50,    66,    75,    76,    54,    55,    56,    57,    58,    53,
      75,    76,   126,    47,    48,    85,    66,    27,   120,    66,
      50,    71,    32,    73,   117,    75,    76,    51,    53,    28,
      83,    56,    53,    32,    51,    85,     4,     5,     6,     7,
      52,    94,    95,    96,    54,    56,     3,     4,     5,     6,
       7,     8,    51,   118,    52,    51,    53,     3,     4,     5,
       6,     7,    19,    51,    32,    75,    76,    51,   118,   162,
     120,   118,   125,   126,   127,    32,    51,    42,    43,    44,
     133,   134,    47,    48,    51,   165,    32,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,    50,    37,   157,   155,   220,   221,    54,   202,
      51,    51,   205,    51,    51,   165,    52,    50,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    52,   222,
       3,     4,     5,     6,     7,    51,    50,   230,   231,   232,
     233,   206,     3,     4,     5,     6,     7,    32,    52,    52,
     203,   204,    32,    50,    50,   208,   206,   210,    50,    32,
       3,     4,     5,     6,     7,    51,    56,   220,   221,    54,
      52,    32,    50,    24,    54,     3,     4,     5,     6,     7,
      52,    54,    52,     3,     4,     5,     6,     7,    52,    32,
      50,    10,   210,    54,     3,     4,     5,     6,     7,     3,
       4,     5,     6,     7,    32,   134,    55,   118,    -1,    -1,
      -1,    54,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    54,    -1,    32,    -1,
       4,     5,     6,     7,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    16,    -1,    18,    54,    -1,    21,    22,    23,
      54,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,     4,     5,     6,     7,    -1,    51,    -1,    53,
      54,    -1,    -1,    -1,    16,    -1,    18,    -1,    -1,    21,
      22,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,     9,    10,    11,    12,    41,
      14,    15,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    53,    54,    -1,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,     9,    10,    11,    12,    -1,
      14,    15,    56,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    -1,     9,    10,    11,    12,
      55,    14,    15,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    -1,    -1,    -1,    52,
       9,    10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      -1,    -1,    -1,    52,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    -1,    -1,    -1,    52,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    -1,
      -1,    -1,    52,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    50,     9,    10,    11,    12,
      -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    -1,    50,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    -1,
      50,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    -1,    50,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    -1,    50,     9,    10,    11,    12,
      -1,    14,    15,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    -1,    14,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    -1,    -1,    -1,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    48,    38,    39,    40,    41,
      42,    43,    44,     9,    10,    47,    48,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    16,    -1,
      18,    -1,    -1,    21,    22,    23,    -1,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,
      -1,    -1,    16,    51,    18,    53,    54,    21,    22,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    -1,    -1,    -1,    -1,    16,    51,    18,    53,
      54,    21,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    16,    45,    18,    -1,    -1,    -1,
      -1,    51,    -1,    53,    -1,    27,    28,    -1,    30,    31,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    32,    58,
      59,    60,    61,    62,    63,    64,    66,    68,    88,    88,
      88,    88,     0,    60,    50,    28,    88,    51,    17,    20,
      53,    53,    51,    62,    63,    65,    90,    88,    92,    91,
      92,    54,    61,    64,    67,    95,     3,    54,    63,    69,
      93,    65,    88,    52,    56,    20,    53,    53,    56,    54,
      67,    88,    88,    54,    69,    52,    53,    70,    62,    91,
      54,    95,    54,    95,    92,    51,    51,    70,    16,    18,
      21,    22,    23,    25,    26,    27,    28,    29,    30,    31,
      33,    34,    35,    36,    41,    45,    51,    54,    61,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      82,    83,    84,    85,    86,    87,    88,    94,    96,    97,
      53,    54,    54,    65,    65,    51,    51,    51,    80,    88,
      97,    50,    92,    51,    51,    51,    51,    80,    80,    80,
      37,     9,    10,    11,    12,    14,    15,    38,    39,    40,
      41,    42,    43,    44,    47,    48,    50,    51,    54,    71,
      54,    61,    94,    50,    54,    95,    52,    52,    80,    80,
      97,    80,    50,    50,    80,    80,    89,    52,    52,    52,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    88,    81,    89,    54,    54,
      50,    50,    52,    50,    50,    52,    56,    52,    56,    55,
      51,    52,    71,    80,    80,    71,    63,    50,    80,    81,
      50,    50,    24,    52,    52,    80,    97,    80,    97,    71,
      52,    52,    52,    52,    71,    71,    71,    71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    57,    58,    59,    59,    60,    60,    60,    60,    61,
      62,    63,    63,    63,    63,    63,    63,    64,    64,    65,
      65,    66,    66,    66,    66,    66,    66,    66,    66,    67,
      67,    68,    68,    69,    69,    70,    70,    70,    70,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    72,    72,
      73,    74,    74,    74,    74,    75,    75,    76,    77,    78,
      78,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    81,
      81,    82,    82,    82,    82,    82,    83,    84,    85,    86,
      87,    88,    89,    89,    90,    90,    91,    91,    92,    93,
      93,    94,    94,    95,    95,    96,    96,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     1,     2,     6,     6,     1,
       0,     5,     4,     7,     6,     7,     6,     9,     8,     1,
       1,     5,     4,     6,     6,     2,     3,     3,     4,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     7,     5,
       5,     9,     9,     9,     9,     3,     3,     2,     5,     4,
       6,     1,     3,     4,     3,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     2,     6,     1,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     3,     1,     1,
       2,     1,     2,     1,     2,     1,     2,     0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 144 "parser.y" /* yacc.c:1646  */
    {
        (yylsp[0]);
        /* pp2: The @1 is needed to convince
        * yacc to set up yylloc. You can remove
        * it once you have other uses of @n*/
        Program *program = new Program((yyvsp[0].declList));
        // if no errors, advance to next phase
        if (ReportError::NumErrors() == 0){
            program->handle(BuildSymbol::B);
        }

        if(ReportError::NumErrors() == 0){
            program->handle(GenCode::G);
        }

                }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 162 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = (yyvsp[-1].declList))->Append((yyvsp[0].decl));}
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 163 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = new List<Decl*>)->Append((yyvsp[0].decl));}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].varDecl);}
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].fnDecl);}
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].classDecl);}
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.decl) = (yyvsp[0].interfaceDecl);}
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 172 "parser.y" /* yacc.c:1646  */
    {(yyval.varDecl) = (yyvsp[-1].varDecl);}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 177 "parser.y" /* yacc.c:1646  */
    {(yyval.varDecl) = new VarDecl((yyvsp[0].classIdentifier), (yyvsp[-1].type));}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 180 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Type::intType;}
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 181 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Type::doubleType;}
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 182 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Type::boolType;}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 183 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = Type::stringType;}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 184 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = new NamedType((yyvsp[0].classIdentifier));}
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 185 "parser.y" /* yacc.c:1646  */
    {(yyval.type) = new ArrayType(Join((yylsp[-1]), (yylsp[0])), (yyvsp[-1].type)); }
#line 1849 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 190 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.fnDecl) = new FnDecl((yyvsp[-4].classIdentifier), (yyvsp[-5].type), (yyvsp[-2].varDeclList));
                    (yyval.fnDecl)-> SetFunctionBody((yyvsp[0].stmtBlock));
                    }
#line 1858 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 194 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.fnDecl) = new FnDecl((yyvsp[-4].classIdentifier), Type::voidType, (yyvsp[-2].varDeclList));
                    (yyval.fnDecl)-> SetFunctionBody((yyvsp[0].stmtBlock));
                    }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 200 "parser.y" /* yacc.c:1646  */
    {(yyval.varDeclList) = (yyvsp[0].varDeclList);}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 201 "parser.y" /* yacc.c:1646  */
    {(yyval.varDeclList) = new List<VarDecl*>();}
#line 1879 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 209 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-3].classIdentifier), NULL, new List<NamedType*>(), (yyvsp[-1].declList) );
                    }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 212 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-2].classIdentifier), NULL, new List<NamedType*>(),  new List<Decl*>());
                    }
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 215 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-5].classIdentifier), NULL, (yyvsp[-3].namedTypeList), (yyvsp[-1].declList) );
                    }
#line 1903 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 218 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-4].classIdentifier), NULL, (yyvsp[-2].namedTypeList), new List<Decl*>() );
                    }
#line 1911 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 221 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-5].classIdentifier), (yyvsp[-3].namedType), new List<NamedType*>(), (yyvsp[-1].declList) );
                    }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 224 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-4].classIdentifier), (yyvsp[-2].namedType), new List<NamedType*>(), new List<Decl*>());
                    }
#line 1927 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 227 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-7].classIdentifier), (yyvsp[-5].namedType), (yyvsp[-3].namedTypeList), (yyvsp[-1].declList) );
                    }
#line 1935 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 230 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.classDecl) = new ClassDecl((yyvsp[-6].classIdentifier), (yyvsp[-4].namedType), (yyvsp[-2].namedTypeList), new List<Decl*>()  );
                    }
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 235 "parser.y" /* yacc.c:1646  */
    {(yyval.decl) = (yyvsp[0].varDecl);}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 236 "parser.y" /* yacc.c:1646  */
    {(yyval.decl) = (yyvsp[0].fnDecl);}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 241 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.interfaceDecl) = new InterfaceDecl((yyvsp[-3].classIdentifier), (yyvsp[-1].declList));
                }
#line 1963 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 244 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.interfaceDecl) = new InterfaceDecl((yyvsp[-2].classIdentifier), new List<Decl*>());
                }
#line 1971 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 249 "parser.y" /* yacc.c:1646  */
    {(yyval.fnDecl) = new FnDecl((yyvsp[-4].classIdentifier), (yyvsp[-5].type), (yyvsp[-2].varDeclList));}
#line 1977 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 250 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.fnDecl) = new FnDecl((yyvsp[-4].classIdentifier), Type::voidType, (yyvsp[-2].varDeclList));
                    }
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 256 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>(), new List<Stmt*>() );
                    }
#line 1993 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 259 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtBlock) = new StmtBlock(new List<VarDecl*>(), (yyvsp[-1].stmtList) );
                    }
#line 2001 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 262 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtBlock) = new StmtBlock((yyvsp[-1].varDeclList), new List<Stmt*>() );
                    }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 265 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.stmtBlock) = new StmtBlock((yyvsp[-2].varDeclList), (yyvsp[-1].stmtList));
                    }
#line 2017 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 270 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[-1].emptyExpr);}
#line 2023 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 271 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[-1].expr);}
#line 2029 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 272 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].ifStmt);}
#line 2035 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 273 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].whileStmt);}
#line 2041 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 274 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].forStmt);}
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 275 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].breakStmt);}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 276 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].returnStmt);}
#line 2059 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 277 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].printStmt);}
#line 2065 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 278 "parser.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmtBlock);}
#line 2071 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 282 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifStmt) = new IfStmt((yyvsp[-4].expr), (yyvsp[-2].stmt), (yyvsp[0].stmt));
                    }
#line 2079 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 285 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.ifStmt) = new IfStmt((yyvsp[-2].expr), (yyvsp[0].stmt), NULL);
                    }
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 291 "parser.y" /* yacc.c:1646  */
    {(yyval.whileStmt) = new WhileStmt((yyvsp[-2].expr), (yyvsp[0].stmt));}
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 295 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forStmt) = new ForStmt((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt));
                    }
#line 2101 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 298 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forStmt) = new ForStmt((yyvsp[-6].expr), (yyvsp[-4].expr), (yyvsp[-2].emptyExpr), (yyvsp[0].stmt));
                    }
#line 2109 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 301 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forStmt) = new ForStmt((yyvsp[-6].emptyExpr), (yyvsp[-4].expr), (yyvsp[-2].expr), (yyvsp[0].stmt));
                    }
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 304 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.forStmt) = new ForStmt((yyvsp[-6].emptyExpr), (yyvsp[-4].expr), (yyvsp[-2].emptyExpr), (yyvsp[0].stmt));
                    }
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 310 "parser.y" /* yacc.c:1646  */
    {(yyval.returnStmt) = new ReturnStmt((yylsp[-1]), (yyvsp[-1].expr));}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 311 "parser.y" /* yacc.c:1646  */
    {(yyval.returnStmt) = new ReturnStmt((yylsp[-1]), (yyvsp[-1].emptyExpr));}
#line 2137 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 315 "parser.y" /* yacc.c:1646  */
    {(yyval.breakStmt) =  new BreakStmt((yylsp[-1]));}
#line 2143 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 319 "parser.y" /* yacc.c:1646  */
    {(yyval.printStmt) = new PrintStmt((yyvsp[-2].exprList)); }
#line 2149 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 322 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.call) = new Call(Join((yylsp[-3]), (yylsp[0])), NULL, (yyvsp[-3].classIdentifier), (yyvsp[-1].exprList));
                    }
#line 2157 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 325 "parser.y" /* yacc.c:1646  */
    {
                    (yyval.call) = new Call(Join((yylsp[-5]), (yylsp[-2])), (yyvsp[-5].expr), (yyvsp[-3].classIdentifier), (yyvsp[-1].exprList));
                    }
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 331 "parser.y" /* yacc.c:1646  */
    {(yyval.lvalue) = new FieldAccess(NULL, (yyvsp[0].classIdentifier));}
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 332 "parser.y" /* yacc.c:1646  */
    {(yyval.lvalue) = new FieldAccess((yyvsp[-2].expr), (yyvsp[0].classIdentifier));}
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 333 "parser.y" /* yacc.c:1646  */
    {(yyval.lvalue) = new ArrayAccess(Join((yylsp[-3]), (yylsp[0])), (yyvsp[-3].expr), (yyvsp[-1].expr));}
#line 2183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 336 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "=");
                    (yyval.expr) = new AssignExpr((yyvsp[-2].lvalue), op, (yyvsp[0].expr));
                    }
#line 2192 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 340 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr);}
#line 2198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 341 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].lvalue);}
#line 2204 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 342 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new This((yylsp[0]));}
#line 2210 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 343 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].call);}
#line 2216 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 344 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr);}
#line 2222 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 345 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "+");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 349 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "-");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 353 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "*");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2249 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 357 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "/");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2258 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 361 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "%");
                    (yyval.expr) = new ArithmeticExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 365 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]),  "-");
                    (yyval.expr) = new ArithmeticExpr(op, (yyvsp[0].expr));
                    }
#line 2276 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 369 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "<");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 373 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "<=");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2294 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 377 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), ">");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 381 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), ">=");
                    (yyval.expr) = new RelationalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 385 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "==");
                    (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 389 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "!=");
                    (yyval.expr) = new EqualityExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2330 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 393 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "&&");
                    (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2339 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 397 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "||");
                    (yyval.expr) = new LogicalExpr((yyvsp[-2].expr), op, (yyvsp[0].expr));
                    }
#line 2348 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 401 "parser.y" /* yacc.c:1646  */
    {
                    Operator * op = new Operator((yylsp[-1]), "!");
                    (yyval.expr) = new LogicalExpr(op, (yyvsp[0].expr));
                    }
#line 2357 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 405 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadIntegerExpr(Join((yylsp[-2]), (yylsp[0])));}
#line 2363 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 406 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ReadLineExpr(Join((yylsp[-2]), (yylsp[0])));}
#line 2369 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 407 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new NewExpr(Join((yylsp[-1]), (yylsp[0])), (yyvsp[0].namedType));}
#line 2375 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 408 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = new
                NewArrayExpr(Join((yylsp[-5]), (yylsp[0])), (yyvsp[-3].expr), (yyvsp[-1].type));}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 414 "parser.y" /* yacc.c:1646  */
    {(yyval.exprList) = (yyvsp[0].exprList);}
#line 2388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 415 "parser.y" /* yacc.c:1646  */
    {(yyval.exprList) = new List<Expr*>();}
#line 2394 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 418 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].classIntConstant);}
#line 2400 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 419 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].classDoubleConstant);}
#line 2406 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 420 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].classBoolConstant);}
#line 2412 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 421 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].classStringConstant);}
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 422 "parser.y" /* yacc.c:1646  */
    {(yyval.expr) = (yyvsp[0].classNullConstant);}
#line 2424 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 425 "parser.y" /* yacc.c:1646  */
    {(yyval.classIntConstant) = new IntConstant((yylsp[0]), (yyvsp[0].integerConstant));}
#line 2430 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 428 "parser.y" /* yacc.c:1646  */
    {(yyval.classDoubleConstant) = new DoubleConstant((yylsp[0]), (yyvsp[0].doubleConstant));}
#line 2436 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 431 "parser.y" /* yacc.c:1646  */
    {(yyval.classBoolConstant) = new BoolConstant((yylsp[0]), (yyvsp[0].boolConstant));}
#line 2442 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 434 "parser.y" /* yacc.c:1646  */
    {(yyval.classStringConstant) = new StringConstant((yylsp[0]), (yyvsp[0].stringConstant));}
#line 2448 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 437 "parser.y" /* yacc.c:1646  */
    {(yyval.classNullConstant) = new NullConstant((yylsp[0]));}
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 440 "parser.y" /* yacc.c:1646  */
    {(yyval.classIdentifier) = new Identifier((yylsp[0]), (yyvsp[0].identifier));}
#line 2460 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 443 "parser.y" /* yacc.c:1646  */
    {((yyval.exprList) = new List<Expr*>())->Append((yyvsp[0].expr));}
#line 2466 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 444 "parser.y" /* yacc.c:1646  */
    {((yyval.exprList) = (yyvsp[-2].exprList))->Append((yyvsp[0].expr));}
#line 2472 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 447 "parser.y" /* yacc.c:1646  */
    {((yyval.varDeclList) = new List<VarDecl*>())->Append((yyvsp[0].varDecl));}
#line 2478 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 448 "parser.y" /* yacc.c:1646  */
    {((yyval.varDeclList) = (yyvsp[-2].varDeclList))->Append((yyvsp[0].varDecl));}
#line 2484 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 451 "parser.y" /* yacc.c:1646  */
    {((yyval.namedTypeList) = new List<NamedType*>())->Append((yyvsp[0].namedType));}
#line 2490 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 452 "parser.y" /* yacc.c:1646  */
    {((yyval.namedTypeList) = (yyvsp[-2].namedTypeList))->Append((yyvsp[0].namedType));}
#line 2496 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 455 "parser.y" /* yacc.c:1646  */
    {(yyval.namedType) = new NamedType((yyvsp[0].classIdentifier));}
#line 2502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 458 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = new List<Decl*>())->Append((yyvsp[0].fnDecl));}
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 459 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = (yyvsp[-1].declList))->Append((yyvsp[0].fnDecl));}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 462 "parser.y" /* yacc.c:1646  */
    {((yyval.stmtList) = new List<Stmt*>())->Append((yyvsp[0].stmt));}
#line 2520 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 463 "parser.y" /* yacc.c:1646  */
    {((yyval.stmtList) = (yyvsp[-1].stmtList))->Append((yyvsp[0].stmt));}
#line 2526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 466 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = new List<Decl*>())->Append((yyvsp[0].decl));}
#line 2532 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 467 "parser.y" /* yacc.c:1646  */
    {((yyval.declList) = (yyvsp[-1].declList))->Append((yyvsp[0].decl));}
#line 2538 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 470 "parser.y" /* yacc.c:1646  */
    {((yyval.varDeclList) = new List<VarDecl*>())->Append((yyvsp[0].varDecl));}
#line 2544 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 471 "parser.y" /* yacc.c:1646  */
    {((yyval.varDeclList) = (yyvsp[-1].varDeclList))->Append((yyvsp[0].varDecl));}
#line 2550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 474 "parser.y" /* yacc.c:1646  */
    {(yyval.emptyExpr) = new EmptyExpr();}
#line 2556 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2560 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 477 "parser.y" /* yacc.c:1906  */


void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
