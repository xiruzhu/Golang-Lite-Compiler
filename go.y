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

%token break_
%token case_
%token chan_
%token const_
%token continue_
%token default_
%token defer_
%token else_
%token fallthrough_
%token for_
%token func_
%token go_
%token goto_
%token if_
%token import_
%token interface_
%token map_
%token package_
%token range_
%token return_
%token select_
%token struct_
%token switch_
%token type_
%token var_
%token bool_
%token rune_
%token string_
%token print_
%token println_
%token append_
%token minus_
%token mult_
%token div_
%token mod_
%token amp_
%token caret_
%token ls_
%token rs_
%token unknown_
%token add_eq_
%token minus_eq_
%token mult_eq_
%token div_eq_
%token mod_eq_
%token amp_eq_
%token vb_eq_
%token caret_eq_
%token ls_eq_
%token rs_eq_
%token unknown_eq_
%token and_
%token or_
%token arrow_
%token incre_
%token decre_
%token equality_
%token lt_
%token gt_
%token eq_
%token not_
%token not_eq_
%token lteq_
%token gteq_
%token decla_
%token etc_
%token lrbrac_
%token rrbrac_
%token lsbrac_
%token rsbrac_
%token lcbrac_
%token rcbrac_
%token comma_
%token dot_
%token colon_
%token vb_
%token int_lit_
%token float_
%token string_lit_
%token semi_colon_
%token ID_
%token new_line_
%token error_

%start go_prog
%left add_ minus_
%left mult_ div_
%left uminus_

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
