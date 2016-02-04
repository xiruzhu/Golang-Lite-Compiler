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
};
%}

%union{ //The types of values we may store
  int     int_val;
  float   float_val;
  char *  str_val;
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
%token int_
%token float_
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
%token id_
%token new_line_
%token error_

%glr-parser
%expect-rr 0

%start go_prog

%left or_
%left and_
%left eq_ not_eq_ lt_ gt_ lteq gteq_
%left add_ minus_ vb_ caret_
%left mult_ div_ mod_ ls_ rs_ amp_ unknown_
%left unary
%%

line_end            : semi_colon_ new_line_
                    : semi_colon
                    | new_line_

nl                  : new_line_
                    | /*empty*/

id_list             : id_
                    | id_list id_

empty_rbrac         : lrbrac_ rrbrac_
empty_sbrac         : lsbrac_ lsbrac_
empty_cbrac         : lcbrac_ lcbrac_

//A go program is composed of a package declaration and multiple top_level declarations
go_prog             : pckg_decl top_decl_list line_end
                    | top_decl_list line_end
                    | /* empty */

pckg_decl           : nl package_ id_ line_end


// function test()

// function test1()
top_decl_list       : nl top_decl line_end
                    | top_decl_list top_decl line_end

top_decl            : decl | func_decl

decl                : type_decl | var_decl

//temp
func_decl           : if_

//temp
var_decl            : switch_

type_decl           : type_ type_spec
                    | type_ lrbrac_ type_spec_list rrbrac_ line_end

type_spec_list      : type_spec line_end
                    | type_spec_list type_spec line_end

type_spec           : id_ type

type                : type_name
                    | type_lit
                    | lrbrac_ type rrbrac_

type_name           : id_
                    | id_ dot_ id_

type_lit            : array_type
                    | struct_type
                    | pointer_type
                    | func_type
                    | slice_type

array_type          : lsbrac_ expr rsbrac_ type

//Struct type
struct_type         : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list     : field_decl line_end
                    | field_decl_list field_decl line_end

field_decl          : id_list type tag
                    | id_list type
                    | anon_field tag
                    | anon_field

tag                 : string_lit_

anon_field          : mult_ type_name
                    | type_name

//Pointer Type
pointer_type        : mult_ type


slice_type          : lsbrac_ rsbrac_ type

func_type           : or_
expr                : float_lit_

%%


















/*
go_prog             : pckg_decl
                    | pckg_decl top_level_decl
                    | block

block               : lcbrac_ rcbrac_

pckg_decl           : package_ id_
                    | package_ id_ pckg_decl

func_decl           : func_ id_ function
                    | func_ id_ signature

func_body           : block

function            : signature func_body

//Function Types
func_type           : func_ signature

signature           : params
                    | params result

result              : type

params              : lrbrac_ rrbrac_
                    | lrbrac_ params_list rrbrac_

params_list         : params_decl
                    | params_list comma_ params_decl

params_decl         : id_list etc_ type
                    | etc_ type
                    | id_list type
                    | type

id_list             : id_
                    | id_list comma_ id_

type                : type_name
                    | type_lit
                    | lrbrac_ type rrbrac_

type_name           : literal_type
                    | id_ dot_ id_

type_lit            : array_type
                    | struct_type
                    | pointer_type
                    | func_type
                    | slice_type

array_type          : lsbrac_ expr rsbrac_ type


//Struct type
struct_type         : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list     : field_decl semi
                    | field_decl_list field_decl semi

field_decl          : id_list type tag
                    | id_list type
                    | anon_field tag
                    | anon_field

tag                 : string_lit_

anon_field          : mult_ type_name
                    | type_name

//Pointer Type
pointer_type        : mult_ base_type

base_type           : type


slice_type          : lsbrac_ rsbrac_ type

semi                : semi_colon_
                    | new_line_

literal_type        : bool_
                    | rune_
                    | string_
                    | float_
                    | int_


//Declarations in General

decl                : type_decl
                    | var_decl

top_level_decl      : decl
                    | func_decl

//Type Declaration

type_decl           : type_ type_spec
                    | type_ lrbrac_ type_spec_list rrbrac_

type_spec           : id_ type

type_spec_list      : type_spec
                    | type_spec comma_ type_spec

//Variable Declaration

var_decl            : "var" var_spec
                    | lrbrac_  var_spec_list rrbrac_
                    | short_var_decl

var_spec            : id_list eq_ expr_list
                    | id_list type eq_ expr_list
                    | id_list type

var_spec_list       : var_spec
                    | var_spec_list semi_colon_ var_spec

short_var_decl      : id_list decla_ expr_list

expr_list           : expr
                    | expr_list comma_ expr

expr                : unary_expr
                    | expr binary_op unary_expr  //it should be expr but in general it's the same


unary_expr          : primary_expr
                    | unary_op unary_expr

binary_op           : or_
                    | and_
                    | rel_op
                    | add_op
                    | mul_op

rel_op              : eq_
                    | not_eq_
                    | lt_
                    | lteq_
                    | gt_
                    | gteq_

add_op              : add_
                    | minus_
                    | vb_
                    | caret_

mul_op              : mult_
                    | div_
                    | mod_
                    | ls_
                    | rs_
                    | amp_
                    | unknown_

unary_op            : add_
                    | minus_
                    | vb_
                    | caret_
                    | mult_
                    | amp_
                    | arrow_

primary_expr        : int_lit_
*/
