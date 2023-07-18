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
#line 1 "sql.ypp" /* yacc.c:339  */

/* C declarations */

#include <stdio.h>
#include <string.h> // for strcmp

//#include <iostream>
#include "expression.hpp"
#include "parser.hpp"

int yylex();
int yyerror( char * s);
int yy_scan_string ( char *yy_str  );
int scan_buffer(const char * data);
static void cmp_fn(Expression * xp1, Expression * xp2);


#line 84 "sql.tab.cpp" /* yacc.c:339  */

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
   by #include "sql.tab.hpp".  */
#ifndef YY_YY_SQL_TAB_HPP_INCLUDED
# define YY_YY_SQL_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SELECT = 258,
    DISTINCT = 259,
    SELECT_OPT = 260,
    FROM = 261,
    WHERE = 262,
    JOIN_TYPE = 263,
    JOIN = 264,
    STRAIGHT_JOIN = 265,
    INDEX = 266,
    USE = 267,
    ON = 268,
    USING = 269,
    IGNORE = 270,
    FORCE = 271,
    FOR = 272,
    QUICK = 273,
    LOW_PRIORITY = 274,
    GROUP = 275,
    ORDER = 276,
    BY = 277,
    ASC = 278,
    DESC = 279,
    INSERT = 280,
    UPDATE = 281,
    DELETE = 282,
    SHOW = 283,
    INTO = 284,
    AS = 285,
    IN = 286,
    ANY = 287,
    EXISTS = 288,
    IS = 289,
    NULLX = 290,
    UNKNOWN = 291,
    FALSEX = 292,
    TRUEX = 293,
    DEFAULT = 294,
    EQUAL = 295,
    N_EQUAL = 296,
    MULTIPLY = 297,
    DIVIDE = 298,
    POWER = 299,
    NEWLINE = 300,
    SHIFT = 301,
    BASIC_OP = 302,
    BETWEEN = 303,
    CASE = 304,
    WHEN = 305,
    THEN = 306,
    ELSE = 307,
    END_CASE = 308,
    CAST = 309,
    DATA_TYPE = 310,
    BINARY = 311,
    CHAR_TYPE = 312,
    REGEXP = 313,
    HAVING = 314,
    LIMIT = 315,
    OFFSET = 316,
    PROCEDURE = 317,
    UNION = 318,
    SET = 319,
    INTEGER = 320,
    STRING = 321,
    Q_STRING = 322,
    DQ_STRING = 323,
    NAME = 324,
    VARIABLE = 325,
    O_BRACE = 326,
    C_BRACE = 327,
    BIT_OR = 328,
    BIT_AND = 329,
    NEG = 330,
    END = 331,
    COMMA = 332,
    DOT = 333,
    AND = 334,
    OR = 335,
    NOT = 336,
    XOR = 337,
    LIKE = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "sql.ypp" /* yacc.c:355  */

  int int_val;
  class SQLString * str_val;
  class Expression * exp_val;

#line 214 "sql.tab.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SQL_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 231 "sql.tab.cpp" /* yacc.c:358  */

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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   831

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  196
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  369

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   338

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    96,    96,    97,    98,    99,   100,   101,   104,   105,
     108,   111,   114,   117,   120,   121,   124,   125,   126,   127,
     128,   131,   132,   135,   136,   137,   138,   139,   140,   143,
     144,   145,   148,   149,   150,   151,   154,   155,   158,   159,
     162,   163,   164,   165,   166,   167,   168,   169,   172,   173,
     174,   175,   176,   177,   178,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   213,   217,   218,   219,   222,   223,   224,
     225,   226,   227,   230,   231,   232,   233,   234,   235,   236,
     237,   240,   241,   244,   245,   248,   251,   252,   253,   256,
     257,   260,   261,   262,   265,   266,   269,   270,   274,   277,
     278,   279,   282,   283,   284,   285,   289,   290,   291,   293,
     294,   295,   298,   299,   302,   303,   304,   307,   308,   309,
     312,   313,   316,   317,   319,   322,   324,   325,   328,   329,
     330,   331,   332,   333,   336,   337,   340,   341,   344,   345,
     346,   349,   350,   353,   354,   357,   358,   359,   360,   363,
     364,   365,   366,   369,   370,   373,   374,   377,   378,   381,
     382,   383,   384,   387,   388,   389,   390,   394,   395,   398,
     401,   402,   403,   404,   405,   406,   407
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SELECT", "DISTINCT", "SELECT_OPT",
  "FROM", "WHERE", "JOIN_TYPE", "JOIN", "STRAIGHT_JOIN", "INDEX", "USE",
  "ON", "USING", "IGNORE", "FORCE", "FOR", "QUICK", "LOW_PRIORITY",
  "GROUP", "ORDER", "BY", "ASC", "DESC", "INSERT", "UPDATE", "DELETE",
  "SHOW", "INTO", "AS", "IN", "ANY", "EXISTS", "IS", "NULLX", "UNKNOWN",
  "FALSEX", "TRUEX", "DEFAULT", "EQUAL", "N_EQUAL", "MULTIPLY", "DIVIDE",
  "POWER", "NEWLINE", "SHIFT", "BASIC_OP", "BETWEEN", "CASE", "WHEN",
  "THEN", "ELSE", "END_CASE", "CAST", "DATA_TYPE", "BINARY", "CHAR_TYPE",
  "REGEXP", "HAVING", "LIMIT", "OFFSET", "PROCEDURE", "UNION", "SET",
  "INTEGER", "STRING", "Q_STRING", "DQ_STRING", "NAME", "VARIABLE",
  "O_BRACE", "C_BRACE", "BIT_OR", "BIT_AND", "NEG", "END", "COMMA", "DOT",
  "AND", "OR", "NOT", "XOR", "LIKE", "$accept", "command", "select_cmd",
  "insert_cmd", "show_cmd", "delete_cmd", "update_cmd", "select_options",
  "select_opts", "delete_option_list", "delete_option",
  "delete_table_list", "delete_table", "where_cond", "select_exps",
  "select_exp", "math_op", "logical_exp", "math_exp", "field",
  "table_field", "const_value", "table_references", "table_reference",
  "join_table", "join_ops", "join_types", "join_cond", "table_factor",
  "simple_table", "alias", "alias_str", "index_hint", "index_use",
  "index_list", "fn", "simple_fn", "fn_args", "logical_operator",
  "logical_exp_list", "comp_operator", "group_cond", "groupby_column_list",
  "sort_order", "having_cond", "order_cond", "orderby_column_list",
  "limit_cond", "procedure_cond", "union_cond", "end_cond", "set_cond",
  "case_fn", "case_cases", "case_case", "cast_fn", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
# endif

#define YYPACT_NINF -275

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-275)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     169,   161,    26,   243,   243,  -275,    32,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,   558,   106,  -275,  -275,  -275,
    -275,    80,   260,    80,  -275,  -275,  -275,  -275,  -275,  -275,
     687,   608,    -8,   664,    -2,  -275,   -33,  -275,  -275,    85,
    -275,   236,     9,  -275,   323,   757,  -275,  -275,  -275,  -275,
    -275,  -275,  -275,  -275,  -275,  -275,  -275,   116,   -38,   235,
    -275,  -275,    37,  -275,  -275,  -275,    14,  -275,    89,   -22,
     120,  -275,   583,   695,   258,  -275,   664,   757,   516,   166,
      56,    75,   133,   704,    80,   558,    86,   151,   171,  -275,
    -275,   664,  -275,  -275,  -275,  -275,  -275,   159,  -275,  -275,
    -275,   664,   687,   687,   687,   687,   687,   687,   687,   182,
      54,    80,  -275,  -275,  -275,    80,   183,    80,   273,    80,
      80,    65,    66,    73,   399,   276,   664,  -275,  -275,   292,
    -275,   757,   -42,   664,   196,  -275,    41,  -275,   199,   213,
    -275,   242,   245,  -275,  -275,    15,  -275,  -275,   664,  -275,
     422,   664,   757,  -275,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,   247,   274,    16,   235,   205,  -275,  -275,   -16,  -275,
    -275,  -275,  -275,   319,    15,  -275,  -275,   255,  -275,  -275,
    -275,  -275,   664,   664,  -275,   717,    -9,  -275,   664,   -11,
    -275,  -275,   301,   302,   310,   313,   475,   338,   103,   664,
     757,   624,   687,   335,   475,   288,  -275,   273,    -1,   335,
     318,   757,   739,  -275,   157,   210,   269,  -275,   339,   296,
    -275,  -275,  -275,  -275,   298,    91,   501,  -275,   380,   127,
    -275,  -275,   350,   314,  -275,   757,  -275,   757,   334,   315,
     127,   664,  -275,   376,   320,   315,  -275,  -275,   664,  -275,
     664,  -275,   664,  -275,    64,  -275,   116,   316,   336,  -275,
     322,   664,   229,   664,  -275,  -275,  -275,   501,    54,   475,
     335,   649,   330,   311,   751,   325,  -275,   109,   311,   111,
     112,   143,  -275,   326,    38,  -275,  -275,    13,   327,  -275,
     236,   518,   329,   757,   664,   402,  -275,  -275,    19,   127,
     315,  -275,   757,   -36,  -275,  -275,  -275,   320,  -275,   320,
    -275,   331,   333,   340,   341,   -18,  -275,  -275,    64,  -275,
    -275,   343,   149,   664,   236,   447,   159,   664,    54,  -275,
     345,   337,   351,   153,  -275,  -275,  -275,  -275,  -275,  -275,
    -275,   757,   346,   174,   159,   664,   664,   757,  -275,   -26,
     362,  -275,  -275,  -275,  -275,  -275,   664,   757,   757,   358,
     360,  -275,   116,   311,   757,   664,   280,  -275,  -275
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    14,     0,    21,    21,    11,     0,     3,     4,     5,
       6,     7,    18,    16,    17,     0,    15,    10,    24,    25,
      23,     0,    22,    29,     1,    97,    98,   100,    99,    41,
       0,     0,     0,     0,     0,    93,    87,    95,    96,    88,
      94,     0,     9,    38,   119,    48,    72,    83,    84,    85,
      86,    51,    52,    20,    19,   116,   117,     0,     0,   101,
     104,   103,   119,    27,    28,    26,     0,    30,    32,    87,
      88,    79,     0,     0,     0,   187,     0,   196,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   148,
     149,     0,   151,   122,   124,   125,   123,     0,   150,    40,
     120,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   107,   108,     0,     0,     0,   126,     0,
       0,     0,     0,     0,     0,     0,     0,   183,   188,     0,
     139,   140,     0,     0,     0,   138,     0,    42,    89,    90,
      43,    91,    92,    82,    81,    36,    39,   121,     0,   152,
       0,     0,    49,    74,    75,    80,    76,    73,    77,    78,
     118,    87,     0,    36,   102,   111,   109,   106,   119,   129,
     130,   131,   114,     0,    36,    31,    35,    33,    89,    90,
      91,    92,     0,     0,   185,     0,     0,   136,     0,   163,
     137,   134,     0,     0,     0,     0,     0,   154,     0,     0,
      50,     0,     0,   163,     0,     0,   105,   126,     0,   163,
       0,   189,     0,   184,     0,     0,     0,   141,     0,     0,
      44,    45,    46,    47,     0,     0,     0,   147,    55,    37,
      70,    71,     0,   161,    54,    53,   180,   179,     0,   169,
     112,     0,   115,     0,     0,   169,    34,   186,     0,   190,
       0,   194,     0,   192,     0,   135,     0,     0,     0,   146,
       0,     0,     0,     0,   142,   143,   144,     0,     0,     0,
     163,     0,     0,   177,     0,     0,   132,     0,   177,     0,
       0,     0,   167,     0,    87,   165,   166,   158,     0,    68,
       0,     0,     0,    58,     0,    56,   145,   156,   158,   162,
     169,   182,   181,   170,   178,    13,   113,     0,   127,     0,
      12,     0,     0,     0,     0,     0,   159,   160,     0,   164,
      69,     0,     0,     0,     0,    57,     0,     0,     0,   155,
     173,     0,     0,     0,   133,   191,   195,   193,   168,    65,
      63,    67,     0,     0,     0,     0,     0,    59,   157,     0,
     175,   172,   171,   128,    66,    64,     0,    60,    61,     0,
       0,   174,     0,   177,    62,     0,     0,   176,     8
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -275,  -275,     0,  -275,  -275,  -275,  -275,  -275,  -275,   394,
    -275,  -275,   281,  -130,  -275,   347,   363,  -165,   -14,   -23,
    -104,  -275,   -55,   344,  -275,  -275,  -275,  -275,   352,   -20,
     -60,   348,   230,  -275,    12,    92,  -245,   -74,  -275,  -193,
     -85,  -275,  -275,   154,  -275,  -175,   138,  -232,  -275,  -275,
    -274,  -275,    -7,   378,   -53,     3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,    82,     8,     9,    10,    11,    15,    16,    21,
      22,    66,    67,   197,    42,    43,    44,   227,   131,    46,
      47,    48,    58,    59,    60,   115,   116,   206,    61,    62,
      99,   100,   172,   173,   277,    49,    50,   132,   267,   229,
     101,   233,   298,   319,   270,   219,   287,   273,   350,   363,
     305,   163,   230,    74,    75,   231
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
       7,    45,   118,    68,   310,   136,   162,    71,    51,   286,
     218,   240,   151,   278,    86,    84,   243,    73,    52,    77,
     119,   128,   196,   196,   134,   331,   110,    83,   239,   145,
     187,   359,    24,   203,   245,   188,   316,   317,    79,   111,
     360,   332,   316,   317,   209,    80,   214,   215,   216,    79,
      93,    94,    95,    96,   135,    17,   122,   109,    45,   189,
     257,   259,   129,    76,   174,    51,   188,    86,   330,    78,
     244,    45,   128,   286,   198,    52,   299,   150,    51,   153,
     154,   155,   156,   157,   158,   159,    85,   152,    52,   368,
     318,   120,   111,   202,     1,   300,   328,   168,   137,   282,
      68,   177,   296,    93,    94,    95,    96,   176,   207,   315,
      53,    54,   185,   191,   217,   117,   122,   140,   188,     1,
     161,   283,   138,    70,   224,   139,    25,    26,    27,    28,
     284,    55,   178,    70,    56,   179,    57,   200,    30,   180,
      31,   141,   181,   263,   142,    32,    55,    33,    34,    56,
     285,    57,    93,    94,    95,    96,    35,    69,    37,    38,
      70,    40,   225,    81,   297,    12,    13,   121,   211,   212,
     133,    14,     1,   263,   279,   234,   280,   294,   281,   238,
     188,   308,   228,   311,   312,   235,   309,   237,   188,   188,
     228,   166,   167,    88,     2,     3,     4,     5,   123,    89,
      90,    25,    26,    27,    28,   143,   264,   265,   134,   266,
     327,   258,   228,    30,   285,   313,   322,    92,   204,   205,
     188,   340,   148,    34,   348,   353,   188,   274,   248,   249,
     309,    35,    69,    37,    38,    70,    40,    41,   135,     1,
     345,   346,    98,   112,   113,   114,   355,   291,   293,   295,
     343,   188,   149,   228,   160,   228,   288,   302,    18,   356,
     292,    19,    20,    88,    25,    26,    27,    28,   190,    89,
      90,    25,    26,    27,    28,    63,    30,   192,    64,    65,
     325,   250,   251,    30,   133,   169,    34,    92,   170,   171,
     321,   193,   136,    34,    35,    69,    37,    38,    70,    40,
      41,    35,    69,    37,    38,    70,    40,    41,    72,   341,
     126,   127,    98,   347,   201,    25,    26,    27,    28,   333,
     194,   334,   186,   195,   342,   122,    72,    30,   183,   184,
     208,   357,   358,   210,   102,   103,   104,    34,   105,   106,
     252,   253,   364,   220,   221,    35,    69,    37,    38,    70,
      40,    41,   222,    86,    87,   223,   218,    88,   232,   241,
     246,   254,   367,    89,    90,   107,   108,   260,   255,   256,
      88,    91,   268,   269,   271,   272,    89,    90,   102,   103,
     104,    92,   105,   106,   261,   275,   276,   304,   289,    93,
      94,    95,    96,   290,    92,   303,   307,   314,    23,   320,
     324,   175,   351,   335,    97,   336,    98,   349,   144,   107,
     108,   260,   337,   130,    88,   339,   352,   262,   354,    98,
      89,    90,   102,   103,   104,   362,   105,   106,   261,   365,
      87,   366,   146,    88,   147,   124,    88,   242,    92,    89,
      90,   361,    89,    90,   102,   103,   104,    91,   105,   106,
     182,   125,   329,   107,   108,   164,   338,    92,     0,     0,
      92,   262,     0,    98,   102,   103,   104,   165,   105,   106,
       0,     0,     0,     0,     0,   107,   108,     0,     0,     0,
      97,    88,    98,   326,     0,    98,     0,    89,    90,   102,
     103,   104,     0,   105,   106,   107,   108,     0,     0,     0,
       0,   199,     0,     0,     0,    92,     0,     0,   224,     0,
      25,    26,    27,    28,     0,     0,     0,     0,     0,     0,
     107,   108,    30,     0,    31,     0,     0,     0,   344,    32,
      98,    33,    34,     0,   224,     0,    25,    26,    27,    28,
      35,    69,    37,    38,    70,    40,   225,     0,    30,     0,
      31,    25,    26,    27,    28,    32,   226,    33,    34,     0,
     102,   103,   104,    30,   105,   106,    35,    69,    37,    38,
      70,    40,   225,    34,     0,     0,     0,     0,     0,     0,
       0,    35,    69,    37,    38,    70,    40,    41,   130,     0,
       0,   107,   108,    25,    26,    27,    28,   323,     0,     0,
      29,     0,     0,     0,     0,    30,     0,    31,     0,     0,
       0,     0,    32,     0,    33,    34,     0,     0,    25,    26,
      27,    28,     0,    35,    36,    37,    38,    39,    40,    41,
      30,     0,    31,     0,     0,     0,     0,    32,     0,    33,
      34,     0,     0,    25,    26,    27,    28,     0,    35,    69,
      37,    38,    70,    40,    41,    30,     0,     0,    72,    25,
      26,    27,    28,   236,     0,    34,     0,     0,     0,     0,
       0,    30,     0,    35,    69,    37,    38,    70,    40,    41,
       0,    34,     0,     0,    25,    26,    27,    28,   301,    35,
      69,    37,    38,    70,    40,    41,    30,     0,     0,    25,
      26,    27,    28,     0,     0,     0,    34,     0,     0,     0,
       0,    30,     0,     0,    35,    69,    37,    38,    70,    40,
      41,    34,    25,    26,    27,    28,     0,     0,     0,    35,
      69,    37,    38,    70,    40,    41,     0,   102,   103,   104,
       0,   105,   106,     0,    34,    72,   102,   103,   104,     0,
     105,   106,    35,    69,    37,    38,    70,    40,     0,   102,
     103,   104,     0,   105,   106,     0,     0,     0,   107,   108,
     213,     0,     0,     0,     0,     0,   144,   107,   108,     0,
       0,   102,   103,   104,     0,   105,   106,     0,     0,     0,
     107,   108,   247,   102,   103,   104,     0,   105,   106,   102,
     103,   104,     0,   105,   106,     0,     0,     0,     0,     0,
       0,     0,   107,   108,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   306,   107,   108,     0,     0,     0,     0,
     107,   108
};

static const yytype_int16 yycheck[] =
{
       0,    15,    62,    23,   278,    79,   110,    30,    15,   254,
      21,   204,    97,   245,    30,     6,    17,    31,    15,    33,
       6,    74,     7,     7,    42,    61,    64,    41,   203,    84,
      72,    57,     0,   163,   209,    77,    23,    24,    71,    77,
      66,    77,    23,    24,   174,    78,    55,    56,    57,    71,
      66,    67,    68,    69,    72,    29,    78,    57,    72,   133,
     225,   226,    76,    71,   119,    72,    77,    30,   300,    71,
      71,    85,   125,   318,   148,    72,   269,    91,    85,   102,
     103,   104,   105,   106,   107,   108,    77,   101,    85,   363,
      77,    77,    77,    77,     3,   270,    77,   117,    42,    35,
     120,   121,   267,    66,    67,    68,    69,    42,   168,    71,
       4,     5,   126,    72,   188,    78,    78,    42,    77,     3,
      66,    57,    66,    69,    33,    69,    35,    36,    37,    38,
      66,    66,    66,    69,    69,    69,    71,   151,    47,    66,
      49,    66,    69,   228,    69,    54,    66,    56,    57,    69,
     254,    71,    66,    67,    68,    69,    65,    66,    67,    68,
      69,    70,    71,    78,   268,     4,     5,    78,   182,   183,
       4,    10,     3,   258,   248,    72,   250,   262,   252,   202,
      77,    72,   196,    72,    72,   199,    77,   201,    77,    77,
     204,     8,     9,    34,    25,    26,    27,    28,    78,    40,
      41,    35,    36,    37,    38,    72,    79,    80,    42,    82,
     295,   225,   226,    47,   318,    72,   290,    58,    13,    14,
      77,    72,    71,    57,   328,    72,    77,   241,    71,    72,
      77,    65,    66,    67,    68,    69,    70,    71,    72,     3,
     325,   326,    83,     8,     9,    10,    72,   261,   262,   263,
     324,    77,    81,   267,    72,   269,   256,   271,    15,   344,
      31,    18,    19,    34,    35,    36,    37,    38,    72,    40,
      41,    35,    36,    37,    38,    15,    47,    78,    18,    19,
     294,    71,    72,    47,     4,    12,    57,    58,    15,    16,
     290,    78,   366,    57,    65,    66,    67,    68,    69,    70,
      71,    65,    66,    67,    68,    69,    70,    71,    50,   323,
      52,    53,    83,   327,    40,    35,    36,    37,    38,   307,
      78,   309,    30,    78,   324,    78,    50,    47,    52,    53,
      11,   345,   346,    78,    42,    43,    44,    57,    46,    47,
      71,    72,   356,    42,    42,    65,    66,    67,    68,    69,
      70,    71,    42,    30,    31,    42,    21,    34,    20,    71,
      42,    22,   362,    40,    41,    73,    74,    31,    72,    71,
      34,    48,    22,    59,    40,    60,    40,    41,    42,    43,
      44,    58,    46,    47,    48,     9,    66,    76,    72,    66,
      67,    68,    69,    71,    58,    65,    71,    71,     4,    72,
      71,   120,    65,    72,    81,    72,    83,    62,    72,    73,
      74,    31,    72,    72,    34,    72,    65,    81,    72,    83,
      40,    41,    42,    43,    44,    63,    46,    47,    48,    71,
      31,    71,    85,    34,    86,    72,    34,   207,    58,    40,
      41,   349,    40,    41,    42,    43,    44,    48,    46,    47,
      51,    73,   298,    73,    74,   111,   318,    58,    -1,    -1,
      58,    81,    -1,    83,    42,    43,    44,   115,    46,    47,
      -1,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,
      81,    34,    83,    81,    -1,    83,    -1,    40,    41,    42,
      43,    44,    -1,    46,    47,    73,    74,    -1,    -1,    -1,
      -1,    79,    -1,    -1,    -1,    58,    -1,    -1,    33,    -1,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    47,    -1,    49,    -1,    -1,    -1,    81,    54,
      83,    56,    57,    -1,    33,    -1,    35,    36,    37,    38,
      65,    66,    67,    68,    69,    70,    71,    -1,    47,    -1,
      49,    35,    36,    37,    38,    54,    81,    56,    57,    -1,
      42,    43,    44,    47,    46,    47,    65,    66,    67,    68,
      69,    70,    71,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    68,    69,    70,    71,    72,    -1,
      -1,    73,    74,    35,    36,    37,    38,    79,    -1,    -1,
      42,    -1,    -1,    -1,    -1,    47,    -1,    49,    -1,    -1,
      -1,    -1,    54,    -1,    56,    57,    -1,    -1,    35,    36,
      37,    38,    -1,    65,    66,    67,    68,    69,    70,    71,
      47,    -1,    49,    -1,    -1,    -1,    -1,    54,    -1,    56,
      57,    -1,    -1,    35,    36,    37,    38,    -1,    65,    66,
      67,    68,    69,    70,    71,    47,    -1,    -1,    50,    35,
      36,    37,    38,    39,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    65,    66,    67,    68,    69,    70,    71,
      -1,    57,    -1,    -1,    35,    36,    37,    38,    39,    65,
      66,    67,    68,    69,    70,    71,    47,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    65,    66,    67,    68,    69,    70,
      71,    57,    35,    36,    37,    38,    -1,    -1,    -1,    65,
      66,    67,    68,    69,    70,    71,    -1,    42,    43,    44,
      -1,    46,    47,    -1,    57,    50,    42,    43,    44,    -1,
      46,    47,    65,    66,    67,    68,    69,    70,    -1,    42,
      43,    44,    -1,    46,    47,    -1,    -1,    -1,    73,    74,
      53,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,
      -1,    42,    43,    44,    -1,    46,    47,    -1,    -1,    -1,
      73,    74,    53,    42,    43,    44,    -1,    46,    47,    42,
      43,    44,    -1,    46,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,
      73,    74
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    25,    26,    27,    28,    85,    86,    87,    88,
      89,    90,     4,     5,    10,    91,    92,    29,    15,    18,
      19,    93,    94,    93,     0,    35,    36,    37,    38,    42,
      47,    49,    54,    56,    57,    65,    66,    67,    68,    69,
      70,    71,    98,    99,   100,   102,   103,   104,   105,   119,
     120,   136,   139,     4,     5,    66,    69,    71,   106,   107,
     108,   112,   113,    15,    18,    19,    95,    96,   113,    66,
      69,   103,    50,   102,   137,   138,    71,   102,    71,    71,
      78,    78,    86,   102,     6,    77,    30,    31,    34,    40,
      41,    48,    58,    66,    67,    68,    69,    81,    83,   114,
     115,   124,    42,    43,    44,    46,    47,    73,    74,    86,
      64,    77,     8,     9,    10,   109,   110,    78,   114,     6,
      77,    78,    78,    78,   100,   137,    52,    53,   138,   102,
      72,   102,   121,     4,    42,    72,   121,    42,    66,    69,
      42,    66,    69,    72,    72,   106,    99,   115,    71,    81,
     102,   124,   102,   103,   103,   103,   103,   103,   103,   103,
      72,    66,   104,   135,   107,   112,     8,     9,   113,    12,
      15,    16,   116,   117,   106,    96,    42,   113,    66,    69,
      66,    69,    51,    52,    53,   102,    30,    72,    77,   121,
      72,    72,    78,    78,    78,    78,     7,    97,   121,    79,
     102,    40,    77,    97,    13,    14,   111,   114,    11,    97,
      78,   102,   102,    53,    55,    56,    57,   121,    21,   129,
      42,    42,    42,    42,    33,    71,    81,   101,   102,   123,
     136,   139,    20,   125,    72,   102,    39,   102,   103,   129,
     123,    71,   116,    17,    71,   129,    42,    53,    71,    72,
      71,    72,    71,    72,    22,    72,    71,   101,   102,   101,
      31,    48,    81,   124,    79,    80,    82,   122,    22,    59,
     128,    40,    60,   131,   102,     9,    66,   118,   131,   121,
     121,   121,    35,    57,    66,   104,   120,   130,    86,    72,
      71,   102,    31,   102,   124,   102,   101,   104,   126,   123,
     129,    39,   102,    65,    76,   134,    72,    71,    72,    77,
     134,    72,    72,    72,    71,    71,    23,    24,    77,   127,
      72,    86,   121,    79,    71,   102,    81,   124,    77,   127,
     131,    61,    77,   118,   118,    72,    72,    72,   130,    72,
      72,   102,    86,   121,    81,   124,   124,   102,   104,    62,
     132,    65,    65,    72,    72,    72,   124,   102,   102,    57,
      66,   119,    63,   133,   102,    71,    71,    86,   134
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    84,    85,    85,    85,    85,    85,    85,    86,    86,
      87,    88,    89,    90,    91,    91,    92,    92,    92,    92,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    95,
      95,    95,    96,    96,    96,    96,    97,    97,    98,    98,
      99,    99,    99,    99,    99,    99,    99,    99,   100,   100,
     100,   100,   100,   100,   100,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   103,   103,   103,   103,   104,   104,   104,
     104,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   106,   107,   107,   108,   109,   109,   109,   110,
     110,   111,   111,   111,   112,   112,   113,   113,   113,   114,
     114,   114,   115,   115,   115,   115,   116,   116,   116,   117,
     117,   117,   118,   118,   119,   119,   119,   120,   120,   120,
     121,   121,   122,   122,   122,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   125,   125,   126,   126,   127,   127,
     127,   128,   128,   129,   129,   130,   130,   130,   130,   131,
     131,   131,   131,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   135,   136,   136,   136,   136,   137,   137,   138,
     139,   139,   139,   139,   139,   139,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     1,     1,     1,    13,     3,
       2,     1,     9,     9,     0,     1,     1,     1,     1,     2,
       2,     0,     1,     1,     1,     1,     2,     2,     2,     0,
       1,     3,     1,     3,     5,     3,     0,     2,     1,     3,
       2,     1,     3,     3,     5,     5,     5,     5,     1,     3,
       4,     1,     1,     5,     5,     1,     3,     4,     3,     5,
       6,     6,     7,     5,     6,     5,     6,     5,     3,     4,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     4,     2,     1,     1,     2,
       1,     0,     2,     4,     3,     5,     1,     1,     3,     0,
       1,     2,     1,     1,     1,     1,     0,     5,     7,     1,
       1,     1,     1,     3,     4,     6,     4,     4,     3,     3,
       1,     3,     1,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     2,     1,     0,     4,     1,     3,     0,     1,
       1,     0,     2,     0,     4,     1,     1,     1,     3,     0,
       2,     4,     4,     0,     2,     0,     2,     0,     1,     3,
       3,     5,     5,     3,     5,     4,     6,     1,     2,     4,
       6,     9,     6,     9,     6,     9,     2
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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
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

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 104 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-10].exp_val); }
#line 1675 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 105 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1681 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 158 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1687 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 159 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1693 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 162 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 1699 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 163 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); }
#line 1705 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 164 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val)); }
#line 1711 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 165 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val));  }
#line 1717 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 166 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val)); }
#line 1723 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 167 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val)); }
#line 1729 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 168 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val)); }
#line 1735 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 169 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[-2].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[-2].str_val)); }
#line 1741 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 172 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1747 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 173 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1753 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 174 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1759 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 175 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1765 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 176 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1771 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 177 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-4].exp_val); }
#line 1777 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 178 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-4].exp_val); }
#line 1783 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 181 "sql.ypp" /* yacc.c:1646  */
    { if ((yyvsp[0].exp_val)->IsTrue()) clb_found_tautology(); }
#line 1789 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 182 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-2].exp_val),(yyvsp[0].exp_val)); }
#line 1795 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 183 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-3].exp_val),(yyvsp[0].exp_val)); }
#line 1801 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 184 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-2].exp_val),(yyvsp[0].exp_val)); }
#line 1807 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 185 "sql.ypp" /* yacc.c:1646  */
    { clb_found_tautology(); }
#line 1813 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 186 "sql.ypp" /* yacc.c:1646  */
    { clb_found_tautology(); }
#line 1819 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 187 "sql.ypp" /* yacc.c:1646  */
    { clb_found_tautology(); }
#line 1825 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 188 "sql.ypp" /* yacc.c:1646  */
    { clb_found_tautology(); }
#line 1831 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 189 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-4].exp_val),(yyvsp[-1].exp_val)); }
#line 1837 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 190 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-5].exp_val),(yyvsp[-1].exp_val)); }
#line 1843 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 191 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-4].exp_val), (yyvsp[-1].exp_val)); }
#line 1849 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 192 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-5].exp_val), (yyvsp[-1].exp_val)); }
#line 1855 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 193 "sql.ypp" /* yacc.c:1646  */
    { cmp_fn((yyvsp[-4].exp_val), (yyvsp[-2].exp_val)); cmp_fn((yyvsp[-4].exp_val), (yyvsp[0].exp_val)); }
#line 1861 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 200 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1867 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 201 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1873 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 202 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1879 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 203 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1885 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 204 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1891 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 205 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1897 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 206 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 1903 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 207 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1909 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 208 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); /*bit xor*/ }
#line 1915 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 209 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 1921 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 210 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 1927 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 213 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); 
                            clb_check_true_constant((yyvsp[0].str_val))? 
                              (yyval.exp_val)->AddConst(new SQLString("fn()")) : 
                              (yyval.exp_val)->AddField((yyvsp[0].str_val)); }
#line 1936 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 217 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1942 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 218 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 1948 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 219 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst(new SQLString("fn()")); }
#line 1954 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 222 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1960 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 223 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1966 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 224 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1972 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 225 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1978 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 226 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1984 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 227 "sql.ypp" /* yacc.c:1646  */
    { (yyval.str_val)=(yyvsp[0].str_val); }
#line 1990 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 230 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst((yyvsp[0].int_val)); }
#line 1996 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 231 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst((yyvsp[0].int_val)); }
#line 2002 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 232 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst((yyvsp[0].str_val)); }
#line 2008 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 233 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst((yyvsp[0].str_val)); }
#line 2014 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 234 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst(0);  }
#line 2020 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 235 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst(0); }
#line 2026 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 236 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst(1); }
#line 2032 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 237 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddConst(0); }
#line 2038 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 269 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[0].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[0].str_val)); }
#line 2044 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 270 "sql.ypp" /* yacc.c:1646  */
    { clb_found_table((yyvsp[0].str_val)); (yyval.exp_val)=new Expression(); (yyval.exp_val)->AddField((yyvsp[0].str_val)); }
#line 2050 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 274 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 2056 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 277 "sql.ypp" /* yacc.c:1646  */
    { }
#line 2062 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 278 "sql.ypp" /* yacc.c:1646  */
    { }
#line 2068 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 279 "sql.ypp" /* yacc.c:1646  */
    { }
#line 2074 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 282 "sql.ypp" /* yacc.c:1646  */
    { /* $$ = $1; printf("table: %s\n", $1); */ }
#line 2080 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 283 "sql.ypp" /* yacc.c:1646  */
    { /* $$ = $2; printf("table: %s\n", $2); */ }
#line 2086 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 302 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); clb_check_bruteforce_function((yyvsp[-3].str_val)); }
#line 2092 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 303 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-2].exp_val); clb_check_bruteforce_function((yyvsp[-5].str_val)); /* printf("fn\n"); */ }
#line 2098 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 304 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 2104 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 307 "sql.ypp" /* yacc.c:1646  */
    { clb_check_bruteforce_function((yyvsp[-3].str_val)); }
#line 2110 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 308 "sql.ypp" /* yacc.c:1646  */
    { clb_check_bruteforce_function((yyvsp[-2].str_val)); }
#line 2116 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 309 "sql.ypp" /* yacc.c:1646  */
    { /* $1 = new SQLString("char()"); */ }
#line 2122 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 312 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 2128 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 313 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 2134 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 183:
#line 387 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-1].exp_val); }
#line 2140 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 184:
#line 388 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val) = (yyvsp[-3].exp_val); (yyval.exp_val)->Add((yyvsp[-1].exp_val)); }
#line 2146 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 185:
#line 389 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-2].exp_val); cmp_fn((yyvsp[-2].exp_val),(yyvsp[-1].exp_val)); }
#line 2152 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 186:
#line 390 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-4].exp_val); cmp_fn((yyvsp[-4].exp_val),(yyvsp[-3].exp_val)); cmp_fn((yyvsp[-4].exp_val),(yyvsp[-1].exp_val)); (yyval.exp_val)->Add((yyvsp[-1].exp_val)); }
#line 2158 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 187:
#line 394 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val) = (yyvsp[0].exp_val); }
#line 2164 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 188:
#line 395 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)->Add((yyvsp[0].exp_val)); }
#line 2170 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 189:
#line 398 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-2].exp_val); }
#line 2176 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 190:
#line 401 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-3].exp_val); }
#line 2182 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 191:
#line 402 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-6].exp_val); }
#line 2188 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 192:
#line 403 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-3].exp_val); }
#line 2194 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 193:
#line 404 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-6].exp_val); }
#line 2200 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 194:
#line 405 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-3].exp_val); }
#line 2206 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 195:
#line 406 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[-6].exp_val); }
#line 2212 "sql.tab.cpp" /* yacc.c:1646  */
    break;

  case 196:
#line 407 "sql.ypp" /* yacc.c:1646  */
    { (yyval.exp_val)=(yyvsp[0].exp_val); }
#line 2218 "sql.tab.cpp" /* yacc.c:1646  */
    break;


#line 2222 "sql.tab.cpp" /* yacc.c:1646  */
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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
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
#line 410 "sql.ypp" /* yacc.c:1906  */

/*
int main()
{
  std::string s;
  while (std::cin)
  {
    std::getline(std::cin, s);
    //std::cout << "line: " << s << std::endl;
    scan_buffer(s.c_str());
  }
  return 1;
}

*/
int yyerror( char *s)
{
    extern char * yytext;
    //printf("error at char %s\n", yytext);
    //exit(1);
    return 1;
}

static void cmp_fn(Expression * xp1, Expression * xp2)
{
  if (xp1->Comp(xp2))
    clb_found_tautology();
  else if (xp1->IsEmptyPwd(xp2))
    clb_found_empty_pwd();
}
