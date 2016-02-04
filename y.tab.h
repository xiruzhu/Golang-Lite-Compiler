/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2013 Free Software Foundation, Inc.

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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 22 "go.y" /* glr.c:2555  */
 //The types of values we may store
  int     int_val;
  float   float_val;
  char *  str_val;

#line 152 "y.tab.h" /* glr.c:2555  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
