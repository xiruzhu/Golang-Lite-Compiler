/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "go.y" /* yacc.c:339  */

#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>

extern char *yytext; /* string from scanner */
extern int line_num;
extern int line_char;

void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", line_num, s); }
int yylex(void);
union value{
  int     int_val;
  float   float_val;
  char *  str_val;
};


#line 85 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    error_ = 258,
    break_ = 259,
    case_ = 260,
    chan_ = 261,
    const_ = 262,
    continue_ = 263,
    default_ = 264,
    defer_ = 265,
    else_ = 266,
    fallthrough_ = 267,
    for_ = 268,
    func_ = 269,
    go_ = 270,
    goto_ = 271,
    if_ = 272,
    import_ = 273,
    interface_ = 274,
    map_ = 275,
    package_ = 276,
    range_ = 277,
    return_ = 278,
    select_ = 279,
    struct_ = 280,
    switch_ = 281,
    type_ = 282,
    var_ = 283,
    int_ = 284,
    float_ = 285,
    bool_ = 286,
    rune_ = 287,
    string_ = 288,
    print_ = 289,
    println_ = 290,
    append_ = 291,
    ls_ = 292,
    rs_ = 293,
    unknown_ = 294,
    add_eq_ = 295,
    minus_eq_ = 296,
    mult_eq_ = 297,
    div_eq_ = 298,
    mod_eq_ = 299,
    amp_eq_ = 300,
    vb_eq_ = 301,
    caret_eq_ = 302,
    ls_eq_ = 303,
    rs_eq_ = 304,
    unknown_eq_ = 305,
    and_ = 306,
    or_ = 307,
    arrow_ = 308,
    incre_ = 309,
    decre_ = 310,
    equality_ = 311,
    not_eq_ = 312,
    lteq_ = 313,
    gteq_ = 314,
    decla_ = 315,
    etc_ = 316,
    int_lit_ = 317,
    float_lit_ = 318,
    string_lit_ = 319,
    rune_lit_ = 320,
    id_ = 321,
    unary = 322
  };
#endif
/* Tokens.  */
#define error_ 258
#define break_ 259
#define case_ 260
#define chan_ 261
#define const_ 262
#define continue_ 263
#define default_ 264
#define defer_ 265
#define else_ 266
#define fallthrough_ 267
#define for_ 268
#define func_ 269
#define go_ 270
#define goto_ 271
#define if_ 272
#define import_ 273
#define interface_ 274
#define map_ 275
#define package_ 276
#define range_ 277
#define return_ 278
#define select_ 279
#define struct_ 280
#define switch_ 281
#define type_ 282
#define var_ 283
#define int_ 284
#define float_ 285
#define bool_ 286
#define rune_ 287
#define string_ 288
#define print_ 289
#define println_ 290
#define append_ 291
#define ls_ 292
#define rs_ 293
#define unknown_ 294
#define add_eq_ 295
#define minus_eq_ 296
#define mult_eq_ 297
#define div_eq_ 298
#define mod_eq_ 299
#define amp_eq_ 300
#define vb_eq_ 301
#define caret_eq_ 302
#define ls_eq_ 303
#define rs_eq_ 304
#define unknown_eq_ 305
#define and_ 306
#define or_ 307
#define arrow_ 308
#define incre_ 309
#define decre_ 310
#define equality_ 311
#define not_eq_ 312
#define lteq_ 313
#define gteq_ 314
#define decla_ 315
#define etc_ 316
#define int_lit_ 317
#define float_lit_ 318
#define string_lit_ 319
#define rune_lit_ 320
#define id_ 321
#define unary 322

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "go.y" /* yacc.c:355  */
 //This is for clarity
  int   int_val;
  float   float_val;
  char *  str_val;
  struct node * node_val;

#line 266 "y.tab.c" /* yacc.c:355  */
};
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

#line 295 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  68
/* YYNRULES -- Number of rules.  */
#define YYNRULES  172
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   322

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    67,     2,     2,     2,    41,    42,     2,
      77,    78,    39,    37,    79,    38,    80,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    81,    87,
      64,    66,    65,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    74,     2,    73,    43,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    76,    82,    75,     2,     2,     2,     2,
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
      35,    36,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    68,    69,    70,    71,    72,    83,    84,    85,
      86,    88,    89
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   131,   131,   133,   136,   137,   139,   139,   141,   141,
     143,   144,   146,   148,   150,   152,   154,   156,   157,   159,
     161,   162,   164,   164,   166,   168,   169,   171,   172,   174,
     175,   177,   179,   180,   182,   183,   184,   186,   187,   189,
     189,   189,   189,   189,   191,   191,   191,   191,   191,   193,
     194,   196,   203,   204,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   215,   216,   218,   220,   221,   222,   223,
     224,   225,   227,   228,   230,   232,   234,   236,   237,   239,
     240,   242,   243,   246,   247,   249,   251,   253,   253,   255,
     256,   258,   260,   261,   262,   263,   265,   266,   268,   270,
     271,   273,   274,   276,   277,   279,   281,   283,   283,   283,
     283,   283,   283,   283,   283,   283,   283,   283,   285,   291,
     292,   294,   295,   296,   298,   300,   301,   302,   303,   305,
     306,   307,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   328,   328,   328,   328,   330,   331,   333,   335,   336,
     337,   338,   339,   340,   342,   344,   346,   348,   349,   350,
     351,   352,   353
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "error_", "break_", "case_", "chan_",
  "const_", "continue_", "default_", "defer_", "else_", "fallthrough_",
  "for_", "func_", "go_", "goto_", "if_", "import_", "interface_", "map_",
  "package_", "range_", "return_", "select_", "struct_", "switch_",
  "type_", "var_", "int_", "float_", "bool_", "rune_", "string_", "print_",
  "println_", "append_", "'+'", "'-'", "'*'", "'/'", "'%'", "'&'", "'^'",
  "ls_", "rs_", "unknown_", "add_eq_", "minus_eq_", "mult_eq_", "div_eq_",
  "mod_eq_", "amp_eq_", "vb_eq_", "caret_eq_", "ls_eq_", "rs_eq_",
  "unknown_eq_", "and_", "or_", "arrow_", "incre_", "decre_", "equality_",
  "'<'", "'>'", "'='", "'!'", "not_eq_", "lteq_", "gteq_", "decla_",
  "etc_", "']'", "'['", "'}'", "'{'", "'('", "')'", "','", "'.'", "':'",
  "'|'", "int_lit_", "float_lit_", "string_lit_", "rune_lit_", "';'",
  "id_", "unary", "$accept", "go_prog", "pckg_decl", "top_decl_list",
  "top_decl", "decl", "func_decl", "func_name", "function", "func_body",
  "block", "block_tmp", "signature", "result", "params", "params_list",
  "params_decl", "var_decl", "type_decl", "type_spec_list", "type_spec",
  "var_spec_list", "var_spec", "id_list", "type", "basic_type",
  "field_decl_list", "field_decl", "stmt_list", "stmt", "simple_stmt",
  "simple_stmt_v", "assign_stmt", "short_decl", "inc_stmt", "dec_stmt",
  "print_stmt", "println_stmt", "return_stmt", "if_stmt", "switch_stmt",
  "for_stmt", "for_clause", "condition", "for_stmt_clause", "switch_cond",
  "case_clause_list", "case_clause", "switch_case", "if_cond",
  "else_block", "break_stmt", "cont_stmt", "assign_op", "expr_stmt",
  "expr_list", "operand", "operand_name", "literal", "expr", "unary_op",
  "func_call", "append", "primary_expr", "selector", "type_cast", "index",
  "slice", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,    43,    45,    42,
      47,    37,    38,    94,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,    60,    62,    61,    33,   312,   313,
     314,   315,   316,    93,    91,   125,   123,    40,    41,    44,
      46,    58,   124,   317,   318,   319,   320,    59,   321,   322
};
# endif

#define YYPACT_NINF -133

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-133)))

#define YYTABLE_NINF -119

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,   -66,    39,   -36,  -133,  -133,  -133,   -10,   -13,   -62,
     -56,  -133,  -133,  -133,  -133,  -133,  -133,     2,  -133,    17,
      -9,  -133,  -133,     6,    67,   -65,  -133,    19,    17,   -51,
      28,  -133,  -133,  -133,  -133,  -133,   -45,  -133,  -133,  -133,
    -133,   -44,  -133,   630,    23,    60,  -133,   -43,  -133,    77,
    -133,  -133,  -133,    45,  -133,  -133,    61,    62,  -133,    17,
      66,    65,    71,    70,  -133,  -133,  -133,  -133,   630,  -133,
    -133,  -133,  -133,  -133,    76,    80,  -133,  -133,  -133,  1242,
     630,  -133,  -133,    63,  -133,  -133,   630,  -133,    56,  -133,
     176,  -133,  -133,  -133,   -68,  -133,    17,  -133,  -133,    72,
    1058,   630,   630,   630,   630,   630,   630,   630,   630,   630,
     630,   630,   630,   630,   630,   630,   630,   630,   630,   630,
     630,   630,  -133,   265,   325,    73,  -133,  -133,  -133,    80,
    -133,    84,    85,   340,   630,   400,   415,    86,    87,  -133,
    -133,  -133,  -133,  -133,    88,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -55,   682,
    -133,    77,  -133,  -133,    95,  -133,  1104,  1242,    83,    83,
    -133,  -133,  -133,  -133,    83,  -133,  -133,  -133,  1069,  1276,
      75,    75,    75,    75,    75,    75,    83,   475,   920,  -133,
       3,  -133,  -133,  -133,    90,    19,  -133,  -133,   733,   630,
      19,   784,  -133,   886,    91,    78,   835,   490,   550,  -133,
     630,   630,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,   630,  -133,   630,  -133,  -133,
     966,  -133,   570,  -133,   630,  -133,  1242,   151,  -133,   630,
    -133,    92,    11,    94,    52,    80,    80,  1242,    57,  -133,
     630,  -133,  1012,   100,  1242,    -3,  1242,     1,  -133,   101,
    -133,   104,  -133,  1150,  -133,   630,   630,  -133,  -133,  -133,
     630,  -133,  -133,  -133,   111,  -133,  -133,  -133,  1196,  -133,
      80,  -133,  -133,   250
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     5,     2,     0,     0,
       0,     4,     6,     7,     8,     9,    12,     0,    30,     0,
       0,    33,    37,     0,     0,     0,    10,    11,    17,     0,
       0,    44,    45,    48,    47,    46,     0,    43,    31,    39,
      27,     0,    25,     0,     0,    36,    20,     0,    23,     0,
      53,    13,    14,     0,    18,    19,     0,     0,    50,     0,
       0,     0,     0,     0,   151,   152,   153,   154,     0,   125,
     126,   127,   128,   124,     0,    34,   158,   122,   123,   119,
       0,   159,   149,   129,   160,    38,     0,    21,     0,    24,
      71,    15,    28,    29,     0,    40,     0,    26,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,     0,   161,   162,   163,    35,
      22,     0,     0,    71,    71,     0,    71,     0,     0,    16,
      54,    55,    52,    60,     0,    69,    70,    67,    68,    56,
      57,    58,    59,    61,    62,    63,    64,    66,     0,   119,
      41,     0,    49,    42,     0,   121,     0,   120,   140,   139,
     130,   131,   132,   133,   138,   135,   136,   134,   147,   148,
     141,   142,   143,   146,   144,   145,   137,     0,     0,   156,
       0,   164,   105,   106,     0,     0,    87,    88,   119,     0,
       0,   119,    82,     0,     0,     0,   119,     0,     0,    65,
       0,     0,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    75,    76,     0,    51,     0,   165,   170,
       0,   166,     0,   155,    90,    86,   102,    83,    81,    93,
      97,     0,     0,     0,     0,    72,    74,    73,     0,   169,
       0,   168,     0,     0,    89,     0,    92,     0,    78,     0,
      80,     0,   157,     0,   167,     0,    71,   103,   104,    84,
       0,   100,    85,    96,     0,    77,    79,   172,     0,    91,
      99,    53,   171,    98
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,  -133,  -133,   175,  -133,  -133,  -133,  -133,
     -27,  -133,  -133,  -133,  -133,  -133,   106,  -133,  -133,  -133,
     166,  -133,   155,     0,   -19,   -16,  -133,  -133,   -84,  -133,
     -33,  -132,  -133,  -133,  -133,  -133,  -133,  -133,  -133,   -57,
    -133,  -133,  -133,   -34,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,   -41,  -133,  -133,  -133,   -49,
    -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,    11,   140,    13,    17,    26,    51,
     141,    53,    27,    54,    28,    47,    48,    14,    15,    29,
      20,    41,    23,    24,    38,    74,    94,   162,    90,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   195,   196,   197,   205,   257,   273,   274,   200,
     269,   155,   156,   225,   157,   158,    76,    77,    78,    79,
      80,    81,    82,    83,   126,    84,   127,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,   194,    75,    39,     8,    45,   270,   160,    39,    55,
     271,   210,    39,    46,   134,    18,   211,     9,    10,   100,
      22,    21,     4,    22,   102,    49,    19,    56,    59,     1,
      89,   122,    22,    39,    61,    87,    88,    19,    60,     5,
      95,   159,    30,    39,    22,   129,    31,    32,    33,    34,
      35,     6,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,    50,   188,    16,   272,   163,    40,    25,
      39,   233,   102,   190,   198,   201,   203,   206,    49,   259,
     102,    36,    30,    42,   161,    50,    31,    32,    33,    34,
      35,   199,    30,   204,    58,    37,    31,    32,    33,    34,
      35,    85,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   105,   106,   107,   108,    86,   110,   111,   112,
     261,   102,    91,    43,   279,   262,   102,   123,   230,    96,
     124,    36,   226,   125,    22,    39,    44,    99,    92,    93,
     236,    36,    97,   101,   240,    37,    44,   121,    98,   102,
     164,   191,   255,   207,   208,    37,   242,   244,   235,   245,
     246,   192,   193,   237,   227,   209,   247,   234,   239,   258,
     131,   260,    12,   252,   132,   254,   248,   266,   275,   133,
     256,   276,   281,   134,   130,    57,    62,   283,   268,   135,
     253,   263,   136,     9,    10,    31,    32,    33,    34,    35,
     137,   138,    63,    64,    65,     0,   278,   159,     0,    66,
       0,     0,     0,     0,     0,     0,     0,     0,   267,   280,
       0,     0,     0,     0,   159,     0,     0,     0,     0,     0,
       0,     0,     0,    67,     0,     0,     0,     0,     0,     0,
       0,   139,    50,    68,   131,     0,     0,     0,   132,    69,
      70,    71,    72,   133,    73,     0,     0,   134,     0,     0,
       0,     0,     0,   135,     0,     0,   136,     9,    10,    31,
      32,    33,    34,    35,   137,   138,    63,    64,    65,     0,
       0,     0,     0,    66,    31,    32,    33,    34,    35,     0,
       0,    63,    64,    65,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    68,     0,     0,
       0,     0,    67,    69,    70,    71,    72,   -71,    73,     0,
       0,     0,    68,     0,     0,     0,   187,     0,    69,    70,
      71,    72,     0,    73,    31,    32,    33,    34,    35,     0,
       0,    63,    64,    65,     0,     0,     0,     0,    66,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    68,   189,     0,     0,     0,    67,    69,    70,
      71,    72,     0,    73,     0,     0,   -90,    68,     0,     0,
       0,     0,     0,    69,    70,    71,    72,     0,    73,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,    31,    32,    33,    34,    35,     0,
       0,    63,    64,    65,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,    67,    69,    70,    71,    72,   202,    73,     0,
       0,   -95,    68,     0,     0,     0,     0,     0,    69,    70,
      71,    72,     0,    73,    31,    32,    33,    34,    35,     0,
       0,    63,    64,    65,     0,     0,     0,     0,    66,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,     0,   229,     0,
       0,     0,    68,     0,     0,     0,     0,    67,    69,    70,
      71,    72,     0,    73,     0,     0,     0,    68,   241,     0,
       0,     0,     0,    69,    70,    71,    72,     0,    73,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,   243,     0,
       0,     0,     0,    69,    70,    71,    72,    67,    73,     0,
       0,     0,     0,   251,     0,     0,     0,    68,     0,     0,
       0,     0,     0,    69,    70,    71,    72,     0,    73,    31,
      32,    33,    34,    35,     0,     0,    63,    64,    65,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,     0,     0,
       0,     0,     0,    69,    70,    71,    72,     0,    73,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   212,
     213,   214,   215,   216,   217,   218,   219,   220,   221,   222,
     113,   114,     0,   223,   224,   115,   116,   117,     0,     0,
     118,   119,   120,     0,     0,     0,     0,     0,  -118,     0,
       0,     0,     0,     0,   121,     0,     0,     0,     0,  -118,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   113,   114,     0,   223,   224,   115,   116,   117,     0,
       0,   118,   119,   120,     0,     0,     0,     0,     0,   -89,
       0,     0,     0,     0,     0,   121,     0,     0,     0,     0,
    -118,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   222,   113,   114,     0,   223,   224,   115,   116,   117,
       0,     0,   118,   119,   120,     0,     0,     0,     0,     0,
    -101,     0,     0,     0,     0,     0,   121,     0,     0,     0,
       0,  -118,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   113,   114,     0,   223,   224,   115,   116,
     117,     0,     0,   118,   119,   120,     0,     0,     0,     0,
       0,   -94,     0,     0,     0,     0,     0,   121,     0,     0,
       0,     0,  -118,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,   121,     0,
       0,     0,     0,   238,     0,     0,     0,     0,   113,   114,
       0,     0,     0,   115,   116,   117,     0,     0,   118,   119,
     120,     0,     0,   231,     0,     0,     0,     0,     0,     0,
       0,   232,   121,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,     0,     0,   249,
       0,     0,     0,     0,     0,     0,     0,   250,   121,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,     0,     0,     0,   115,   116,   117,     0,     0,
     118,   119,   120,     0,     0,   264,     0,     0,     0,     0,
       0,     0,     0,   265,   121,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,     0,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     0,     0,
       0,   115,   116,   117,     0,     0,   118,   119,   120,     0,
       0,     0,   115,   116,   117,     0,   165,   118,   119,   120,
     121,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,     0,     0,     0,   115,   116,   117,
       0,     0,   118,   119,   120,     0,     0,     0,     0,     0,
       0,     0,   228,     0,     0,     0,   121,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
       0,     0,     0,   115,   116,   117,     0,     0,   118,   119,
     120,     0,     0,   277,     0,     0,     0,     0,     0,     0,
       0,     0,   121,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,     0,     0,   282,
       0,     0,     0,     0,     0,     0,     0,     0,   121,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,     0,     0,     0,   115,   116,   117,     0,     0,
     118,   119,   120,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,     0,   121,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,     0,     0,     0,     0,   115,
     116,   117,     0,     0,   118,   119,   120,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   121
};

static const yytype_int16 yycheck[] =
{
      27,   133,    43,    19,    14,    24,     5,    75,    24,    28,
       9,    66,    28,    78,    17,    77,    71,    27,    28,    68,
      88,    77,    88,    88,    79,    25,    88,    78,    73,    21,
      49,    80,    88,    49,    78,    78,    79,    88,    83,     0,
      59,    90,    25,    59,    88,    86,    29,    30,    31,    32,
      33,    87,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,    76,   123,    88,    75,    96,    87,    77,
      96,    78,    79,   124,   133,   134,   135,   136,    88,    78,
      79,    74,    25,    87,    94,    76,    29,    30,    31,    32,
      33,   134,    25,   136,    76,    88,    29,    30,    31,    32,
      33,    88,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    39,    40,    41,    42,    66,    44,    45,    46,
      78,    79,    87,    66,   266,    78,    79,    74,   187,    73,
      77,    74,   161,    80,    88,   161,    79,    77,    87,    87,
     199,    74,    87,    77,    76,    88,    79,    82,    87,    79,
      88,    88,    11,    77,    77,    88,   207,   208,   195,   210,
     211,    87,    87,   200,    79,    87,   225,    87,    87,    87,
       4,    87,     7,   232,     8,   234,   227,    87,    87,    13,
     239,    87,    81,    17,    88,    29,    41,   281,   255,    23,
     234,   250,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,   265,   266,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   255,   270,
      -1,    -1,    -1,    -1,   283,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,     4,    -1,    -1,    -1,     8,    83,
      84,    85,    86,    13,    88,    -1,    -1,    17,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    67,    83,    84,    85,    86,    87,    88,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,
      85,    86,    -1,    88,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    78,    -1,    -1,    -1,    67,    83,    84,
      85,    86,    -1,    88,    -1,    -1,    76,    77,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    67,    83,    84,    85,    86,    87,    88,    -1,
      -1,    76,    77,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    86,    -1,    88,    29,    30,    31,    32,    33,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    67,    83,    84,
      85,    86,    -1,    88,    -1,    -1,    -1,    77,    78,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    78,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    67,    88,    -1,
      -1,    -1,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,    29,
      30,    31,    32,    33,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    88,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    61,    62,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,    87,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    61,    62,    63,    64,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    -1,
      87,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    61,    62,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,
      -1,    87,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    61,    62,    63,    64,
      65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    82,    -1,    -1,
      -1,    -1,    87,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    82,    -1,
      -1,    -1,    -1,    87,    -1,    -1,    -1,    -1,    58,    59,
      -1,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    58,    59,    -1,    -1,
      -1,    63,    64,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    63,    64,    65,    -1,    78,    68,    69,    70,
      82,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    -1,    -1,    -1,    63,    64,    65,
      -1,    -1,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    82,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      -1,    -1,    -1,    63,    64,    65,    -1,    -1,    68,    69,
      70,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    82,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    -1,    -1,
      68,    69,    70,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    -1,    82,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    -1,    63,
      64,    65,    -1,    -1,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    91,    92,    88,     0,    87,    93,    14,    27,
      28,    94,    95,    96,   107,   108,    88,    97,    77,    88,
     110,    77,    88,   112,   113,    77,    98,   102,   104,   109,
      25,    29,    30,    31,    32,    33,    74,    88,   114,   115,
      87,   111,    87,    66,    79,   114,    78,   105,   106,   113,
      76,    99,   100,   101,   103,   114,    78,   110,    76,    73,
      83,    78,   112,    36,    37,    38,    43,    67,    77,    83,
      84,    85,    86,    88,   115,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   155,    88,    66,    78,    79,   114,
     118,    87,    87,    87,   116,   114,    73,    87,    87,    77,
     149,    77,    79,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    58,    59,    63,    64,    65,    68,    69,
      70,    82,   149,    74,    77,    80,   154,   156,   157,   145,
     106,     4,     8,    13,    17,    23,    26,    34,    35,    75,
      95,   100,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   141,   142,   144,   145,   149,
      75,   113,   117,   114,    88,    78,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,    81,   149,    78,
     145,    88,    87,    87,   121,   132,   133,   134,   149,   120,
     139,   149,    87,   149,   120,   135,   149,    77,    77,    87,
      66,    71,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    61,    62,   143,   114,    79,    78,    73,
     149,    73,    81,    78,    87,   100,   149,   100,    87,    87,
      76,    78,   145,    78,   145,   145,   145,   149,   145,    73,
      81,    73,   149,   133,   149,    11,   149,   136,    87,    78,
      87,    78,    78,   149,    73,    81,    87,   100,   129,   140,
       5,     9,    75,   137,   138,    87,    87,    73,   149,   121,
     145,    81,    73,   118
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    93,    93,    94,    94,    95,    95,
      96,    96,    97,    98,    99,   100,   101,   102,   102,   103,
     104,   104,   105,   105,   106,   107,   107,   108,   108,   109,
     109,   110,   111,   111,   112,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   115,   115,   115,   115,   115,   116,
     116,   117,   118,   118,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   120,   121,   121,   121,   121,
     121,   121,   122,   122,   123,   124,   125,   126,   126,   127,
     127,   128,   128,   129,   129,   130,   131,   132,   132,   133,
     133,   134,   135,   135,   135,   135,   136,   136,   137,   138,
     138,   139,   139,   140,   140,   141,   142,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   144,   145,
     145,   146,   146,   146,   147,   148,   148,   148,   148,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   150,   150,   150,   150,   151,   151,   152,   153,   153,
     153,   153,   153,   153,   154,   155,   156,   157,   157,   157,
     157,   157,   157
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     2,     0,     1,     1,     1,     1,
       3,     3,     1,     2,     1,     2,     3,     1,     2,     1,
       2,     3,     3,     1,     2,     3,     5,     3,     5,     3,
       0,     2,     3,     0,     3,     4,     2,     1,     3,     1,
       3,     4,     4,     1,     1,     1,     1,     1,     1,     2,
       0,     2,     2,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     0,     3,     3,     3,     2,     2,     5,     4,     5,
       4,     3,     2,     3,     5,     5,     3,     1,     1,     1,
       0,     5,     3,     2,     1,     0,     2,     0,     3,     2,
       1,     1,     2,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       2,     1,     1,     1,     1,     4,     3,     6,     1,     1,
       1,     2,     2,     2,     2,     4,     3,     5,     4,     4,
       3,     7,     6
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
      
#line 1909 "y.tab.c" /* yacc.c:1646  */
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
#line 354 "go.y" /* yacc.c:1906  */

