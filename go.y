%{
#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>

extern char *yytext; /* string from scanner */
extern int line_num;
extern int line_char;

void yyerror(char * err_msg) {
					fprintf (stderr ,"Syntax error after \"%s\" at line [%d]\n", yytext, line_num);
					for(int i = 0; i < strlen(yytext); i++)
						printf("Character [%d]: %d\n", i, yytext[i]);
			   }

int yylex(void);

union value{
  int		  int_val;
  float		float_val;
  char *	str_val;
  char    char_val;
};
%}


%union{ //The types of values we may store
  int		  int_val;
  float		float_val;
  char *	str_val;
  char    char_val;
}

%token<str_val> break_
%token<str_val> case_
%token<str_val> chan_
%token<str_val> const_
%token<str_val> continue_
%token<str_val> default_
%token<str_val> defer_
%token<str_val> else_
%token<str_val> fallthrough_
%token<str_val> for_
%token<str_val> func_
%token<str_val> go_
%token<str_val> goto_
%token<str_val> if_
%token<str_val> import_
%token<str_val> interface_
%token<str_val> map_
%token<str_val> package_
%token<str_val> range_
%token<str_val> return_
%token<str_val> select_
%token<str_val> struct_
%token<str_val> switch_
%token<str_val> type_
%token<str_val> var_
%token<str_val> bool_
%token append_
%token print_ println_


%token '+' '-' '*' '/' '%'
%token '&' '|' '^' '<<' '>>' '&^'
%token '+=' '-=' '*=' '/*' '%='
%token '&=' '|=' '^=' '<<=' '>>=' '&^='
%token '&&' '||' '<-' '++' '--'
%token '==' '<' '>' '=' '!'
%token '!=' '<=' '>=' ':=' '...'
%token '(' ')' '[' ']' '{' '}' ';' ':' ',' '.'


%token string_ float_ int_ rune_
%token int_lit_ string_lit_ float_lit_ rune_lit_
%token ID_

%token new_line_
%token error_

%left '||'
%left '&&'
%left '=' '!=' '<' '>' '<=' '>='
%left '+' '-' '|' '^'
%left '*' '/' '%' '<<' '>>' '&' '&^'
%left unary


%%

go_prog     : pckg_decl new_l func_start

pckg_decl   : package_ ID_ new_line_
            | package_ ID_ new_line_ pckg_decl

func_start  : func_ ID_ func_args block_stmt

type        : bool_
            | int_lit_
            | float_
            | string_lit_

new_l       : new_line_
            | new_line_ new_l

func_args   : lrbrac_ func_args_1 rrbrac_ type
            | lrbrac_ func_args_2 rrbrac_ type
            | lrbrac_ func_args_2 rrbrac_
            | lrbrac_ func_args_1 rrbrac_
            | lrbrac_ rrbrac_
            | lrbrac_ rrbrac_ type

func_args_1 : ID_ type
            | ID_ type comma_ func_args_1

func_args_2 : id_comma type

id_comma    : ID_
            | ID_ comma_ id_comma

block_stmt  : lcbrac_ new_l reg_stmt new_l rcbrac_ new_l
            | new_l lcbrac_ reg_stmt new_l rcbrac_ new_l

reg_stmt    :


%%
