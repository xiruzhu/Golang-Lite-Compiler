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
    int_ = 283,
    float_ = 284,
    bool_ = 285,
    rune_ = 286,
    string_ = 287,
    print_ = 288,
    println_ = 289,
    append_ = 290,
    add_ = 291,
    minus_ = 292,
    mult_ = 293,
    div_ = 294,
    mod_ = 295,
    amp_ = 296,
    caret_ = 297,
    ls_ = 298,
    rs_ = 299,
    unknown_ = 300,
    add_eq_ = 301,
    minus_eq_ = 302,
    mult_eq_ = 303,
    div_eq_ = 304,
    mod_eq_ = 305,
    amp_eq_ = 306,
    vb_eq_ = 307,
    caret_eq_ = 308,
    ls_eq_ = 309,
    rs_eq_ = 310,
    unknown_eq_ = 311,
    and_ = 312,
    or_ = 313,
    arrow_ = 314,
    incre_ = 315,
    decre_ = 316,
    equality_ = 317,
    lt_ = 318,
    gt_ = 319,
    eq_ = 320,
    not_ = 321,
    not_eq_ = 322,
    lteq_ = 323,
    gteq_ = 324,
    decla_ = 325,
    etc_ = 326,
    lrbrac_ = 327,
    rrbrac_ = 328,
    lsbrac_ = 329,
    rsbrac_ = 330,
    lcbrac_ = 331,
    rcbrac_ = 332,
    comma_ = 333,
    dot_ = 334,
    colon_ = 335,
    vb_ = 336,
    int_lit_ = 337,
    float_lit_ = 338,
    string_lit_ = 339,
    rune_lit_ = 340,
    semi_colon_ = 341,
    id_ = 342,
    new_line_ = 343,
    error_ = 344,
    lteq = 345,
    unary = 346
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
#define int_ 283
#define float_ 284
#define bool_ 285
#define rune_ 286
#define string_ 287
#define print_ 288
#define println_ 289
#define append_ 290
#define add_ 291
#define minus_ 292
#define mult_ 293
#define div_ 294
#define mod_ 295
#define amp_ 296
#define caret_ 297
#define ls_ 298
#define rs_ 299
#define unknown_ 300
#define add_eq_ 301
#define minus_eq_ 302
#define mult_eq_ 303
#define div_eq_ 304
#define mod_eq_ 305
#define amp_eq_ 306
#define vb_eq_ 307
#define caret_eq_ 308
#define ls_eq_ 309
#define rs_eq_ 310
#define unknown_eq_ 311
#define and_ 312
#define or_ 313
#define arrow_ 314
#define incre_ 315
#define decre_ 316
#define equality_ 317
#define lt_ 318
#define gt_ 319
#define eq_ 320
#define not_ 321
#define not_eq_ 322
#define lteq_ 323
#define gteq_ 324
#define decla_ 325
#define etc_ 326
#define lrbrac_ 327
#define rrbrac_ 328
#define lsbrac_ 329
#define rsbrac_ 330
#define lcbrac_ 331
#define rcbrac_ 332
#define comma_ 333
#define dot_ 334
#define colon_ 335
#define vb_ 336
#define int_lit_ 337
#define float_lit_ 338
#define string_lit_ 339
#define rune_lit_ 340
#define semi_colon_ 341
#define id_ 342
#define new_line_ 343
#define error_ 344
#define lteq 345
#define unary 346

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

#line 242 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
