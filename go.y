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

%start go_prog

%left or_
%left and_
%left eq_ not_eq_ lt_ gt_ lteq gteq_
%left add_ minus_ vb_ caret_
%left mult_ div_ mod_ ls_ rs_ amp_ unknown_
%left unary
%%

go_prog             : pckg_decl
                    | pckg_decl block
                    | block                 //Ok so we can have no packages if we want

block               : lcbrac_ statement_list rcbrac_

pckg_decl           : package_ id_
                    | package_ id_ pckg_decl


//Semicolon
semi                : semi_colon_
                    | new_line_
id_list             : id_
                    | id_ comma_ id_list

statement_list      : statement
                    | statement semi_colon_ statement_list

literal             : float_lit_
                    | int_lit_
                    | rune_lit_
                    | string_lit_

//Declarations in General

decl                : type_decl 
                    | var_decl

top_level_decl      : decl 
                    | func_decl


statement           : decl

//Type Declaration

type_decl           : type_ type_spec
                    | type_ lrbrac_ type_spec_list rrbrac_ 

type_spec           : id_ type

type_spec_list      : type_spec
                    | type_spec comma_ type_spec

//Variable Declaration

var_decl            : "var" var_spec
                    | lrbrac_  var_spec_list rrbrac_

var_spec            : id_list eq_ expr_list
                    | id_list eq_expr_list

var_spec_list       : var_spec
                    | var_spec comma_ var_spec_list

short_var_decl      : id_list decla_ expr_list

// Function Declarations now

func_decl           : func_ func_name function
                    | func_ func_name signature

func_name           : id_

func_body           : block

function            : signature func_body

//Function Types
func_type           : func_ signature

signature           : params
                    | params result

//So there are only two forms in minilang, long form and short form
//Long form
result              : type

params              : lrbrac_ rrbrac_
                    | lrbrac_ params_list rrbrac_
                    | lrbrac_ params_list comma_ rrbrac_

params_list         : params_decl
                    | params_decl comma_ params_list

params_decl         : id_list etc_ type
                    | etc_ type
                    | id_list type
                    | type

//Expression Declarations

eq_expr_list        : type eq_ expr_list
                    | type
 
expr_list           : expr
                    | expr comma_ expr_list

expr                : unary_expr
                    | expr binary_op expr

unary_expr          : primary_expr | unary_op unary_expr

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

primary_expr        : semi

//Type Declaration

type                : type_name
                    | type_lit
                    | lrbrac_ type rrbrac_

type_name           : id_
                    | qualified_id

qualified_id        : package_name dot_ id_

package_name        : id_

type_lit            : array_type
                    | struct_type
                    | pointer_type
                    | slice_type

array_type          : lsbrac_ array_length rsbrac_ elem_type

array_length        : expr

elem_type           : type

struct_type         : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list     : field_decl semi
                    | field_decl semi field_decl_list

field_decl          : id_list type tag
                    | id_list type
                    | anon_field tag
                    | anon_field

tag                 : string_lit_

anon_field          : mult_ type_name
                    | type_name

pointer_type        : mult_ base_type

base_type           : type

slice_type          : lsbrac_ rsbrac_ elem_type

%%

