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
    break_ = 258,
    case_ = 259,
    chan_ = 260,
    const_ = 261,
    continue_ = 262,
    default_ = 263,
    defer_ = 264,
    else_ = 265,
    fallthrough_ = 266,
    for_ = 267,
    func_ = 268,
    go_ = 269,
    goto_ = 270,
    if_ = 271,
    import_ = 272,
    interface_ = 273,
    map_ = 274,
    package_ = 275,
    range_ = 276,
    return_ = 277,
    select_ = 278,
    struct_ = 279,
    switch_ = 280,
    type_ = 281,
    var_ = 282,
    bool_ = 283,
    rune_ = 284,
    string_ = 285,
    print_ = 286,
    println_ = 287,
    append_ = 288,
    add_ = 289,
    minus_ = 290,
    mult_ = 291,
    div_ = 292,
    mod_ = 293,
    amp_ = 294,
    caret_ = 295,
    ls_ = 296,
    rs_ = 297,
    unknown_ = 298,
    add_eq_ = 299,
    minus_eq_ = 300,
    mult_eq_ = 301,
    div_eq_ = 302,
    mod_eq_ = 303,
    amp_eq_ = 304,
    vb_eq_ = 305,
    caret_eq_ = 306,
    ls_eq_ = 307,
    rs_eq_ = 308,
    unknown_eq_ = 309,
    and_ = 310,
    or_ = 311,
    arrow_ = 312,
    incre_ = 313,
    decre_ = 314,
    equality_ = 315,
    lt_ = 316,
    gt_ = 317,
    eq_ = 318,
    not_ = 319,
    not_eq_ = 320,
    lteq_ = 321,
    gteq_ = 322,
    decla_ = 323,
    etc_ = 324,
    lrbrac_ = 325,
    rrbrac_ = 326,
    lsbrac_ = 327,
    rsbrac_ = 328,
    lcbrac_ = 329,
    rcbrac_ = 330,
    comma_ = 331,
    dot_ = 332,
    colon_ = 333,
    vb_ = 334,
    int_lit_ = 335,
    float_lit_ = 336,
    string_lit_ = 337,
    rune_lit_ = 338,
    semi_colon_ = 339,
    id_ = 340,
    new_line_ = 341,
    error_ = 342,
    lteq = 343,
    unary = 344
  };
#endif
/* Tokens.  */
#define break_ 258
#define case_ 259
#define chan_ 260
#define const_ 261
#define continue_ 262
#define default_ 263
#define defer_ 264
#define else_ 265
#define fallthrough_ 266
#define for_ 267
#define func_ 268
#define go_ 269
#define goto_ 270
#define if_ 271
#define import_ 272
#define interface_ 273
#define map_ 274
#define package_ 275
#define range_ 276
#define return_ 277
#define select_ 278
#define struct_ 279
#define switch_ 280
#define type_ 281
#define var_ 282
#define bool_ 283
#define rune_ 284
#define string_ 285
#define print_ 286
#define println_ 287
#define append_ 288
#define add_ 289
#define minus_ 290
#define mult_ 291
#define div_ 292
#define mod_ 293
#define amp_ 294
#define caret_ 295
#define ls_ 296
#define rs_ 297
#define unknown_ 298
#define add_eq_ 299
#define minus_eq_ 300
#define mult_eq_ 301
#define div_eq_ 302
#define mod_eq_ 303
#define amp_eq_ 304
#define vb_eq_ 305
#define caret_eq_ 306
#define ls_eq_ 307
#define rs_eq_ 308
#define unknown_eq_ 309
#define and_ 310
#define or_ 311
#define arrow_ 312
#define incre_ 313
#define decre_ 314
#define equality_ 315
#define lt_ 316
#define gt_ 317
#define eq_ 318
#define not_ 319
#define not_eq_ 320
#define lteq_ 321
#define gteq_ 322
#define decla_ 323
#define etc_ 324
#define lrbrac_ 325
#define rrbrac_ 326
#define lsbrac_ 327
#define rsbrac_ 328
#define lcbrac_ 329
#define rcbrac_ 330
#define comma_ 331
#define dot_ 332
#define colon_ 333
#define vb_ 334
#define int_lit_ 335
#define float_lit_ 336
#define string_lit_ 337
#define rune_lit_ 338
#define semi_colon_ 339
#define id_ 340
#define new_line_ 341
#define error_ 342
#define lteq 343
#define unary 344

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "go.y" /* yacc.c:1909  */
 //The types of values we may store
  int     int_val;
  float   float_val;
  char *  str_val;

#line 238 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
