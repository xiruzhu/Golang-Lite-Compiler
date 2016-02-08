/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 23 "go.y" /* yacc.c:1909  */
 //This is for clarity
  int   int_val;
  float   float_val;
  char *  str_val;
  struct node * node_val;

#line 195 "y.tab.h" /* yacc.c:1909  */
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
