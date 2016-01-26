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
  int     int_val;
  float   float_val;
  char *  str_val;
  char    char_val;
};
%}

%union{ //The types of values we may store
  int     int_val;
  float   float_val;
  char *  str_val;
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
%token add_
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
%token float_lit_
%token string_lit_
%token rune_lit_
%token semi_colon_
%token ID_
%token new_line_
%token error_

%start go_prog

%left or_
%left and_
%left eq_ not_eq_ lt_ gt_ lteq gteq_
%left add_ minus_ vb_ caret_
%left mult_ div_ mod_ ls_ rs_ amp_ unknown_
%left unary
%%

go_prog     : pckg_decl new_l

pckg_decl   : package_ ID_ new_line_
            | package_ ID_ new_line_ pckg_decl

semi        : semi_colon_
            | new_line_

new_l       : new_line_
            | new_line_ new_l

literal     : float_lit_
            | int_lit_
            | rune_lit_
            | string_lit_

type        : type_name
            | type_lit
            | lrbrac_ type rrbrac_

type_name   : ID_
            | qualified_ID

qualified_ID: package_name dot_ ID_

package_name: ID_


type_lit    : array_type
            | struct_type
            | pointer_type
            | slice_type

array_type  : lsbrac_ array_length rsbrac_ elem_type

array_length: expression

elem_type   : type


struct_type : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list : field_decl semi
                | field_decl semi field_decl_list
                | /*empty*/

field_decl  : id_list type
            | anon_field

tag         : string_lit_
            | /*empty*/

id_list     : ID_
            | ID_ comma_ id_list
            | /*empty*/

anon_field  : mult_ type_name
            | type_name

pointer_type: mult_ base_type

base_type   : type

slice_type  : lsbrac_ rsbrac_ elem_type

expression  :

%%

/*
go_prog     : pckg_decl new_l

pckg_decl   : package_ ID_ new_line_
            | package_ ID_ new_line_ pckg_decl



func_start  : func_ ID_ func_args block_stmt

type        : bool_
            | int_lit_
            | float_lit_
            | string_lit_
            | rune_lit_

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

reg_stmt    : minus_




decl_list   : decl
            | decl decl_list

decl        : reg_decl
            | fun_decl

reg_decl    : type_decl
            | var_decl

var_decl    : var_ var_spec
            | var_ lrbrac_ var_spec_list semi rrbrac_

semi        : semi_colon_
            | new_line_

var_spec_list     : var_spec
                  | var_spec var_spec_list
ID_list     : ID_
            | ID_ ID_list



var_spec    : ID_list
*/
