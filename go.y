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

//Here is the deal it cannot parse semi colon terminated stuff without newline
line_end            : semi_colon_
                    | /* empty */

/*
new_line_list       : new_line_list new_line_
                    |
*/

id_list             : id_list comma_ id_
                    | id_
/*
empty_rbrac         : lrbrac_ rrbrac_
empty_sbrac         : lsbrac_ lsbrac_
empty_cbrac         : lcbrac_ lcbrac_
*/
block               : lcbrac_ statement_list rcbrac_

//A go program is composed of a package declaration and multiple top_level declarations
go_prog             : pckg_decl top_decl_list
                    | top_decl_list
                    | /* empty */

pckg_decl           : package_ id_ line_end


// function test()

// function test1()
top_decl_list       : top_decl_list top_decl/* line */
                    | top_decl

top_decl            : decl
                    | func_decl

decl                : type_decl | var_decl

//Function declaration, Broader than necessary
func_decl           : func_type type block  //With return
                    | func_type block //Without return

func_decl_list      : func_decl_list comma_ type_spec
                    | type_spec


//Variable Declaration!!
var_decl            : var_ var_decl_one_line /* line */
                    | var_ lrbrac_ var_decl_mult_line rrbrac_ /* line */

var_decl_mult_line  : var_decl_one_line
                    | var_decl_mult_line /* line */ var_decl_one_line

var_decl_one_line   : id_list type
                    | id_list eq_ expr
                    | id_list type eq_ expr

short_var_decl      : id_list decla_ expr_list

//Type stuff, follows more go specs
type_decl           : type_ type_spec /* line */
                    | type_ lrbrac_ type_spec_list rrbrac_ /* line */

type_spec_list      : type_spec_list type_spec /* line */
                    | type_spec /* line */

type_spec           : id_ type

type                : type_primitive
                    | type_lit
                    | id_ dot_ id_
                    | lrbrac_ type rrbrac_

type_primitive      : bool_
                    | rune_
                    | string_
                    | float_
                    | int_

type_lit            : array_type
                    | struct_type
                    | pointer_type
                    | func_type
                    | slice_type

array_type          : lsbrac_ expr rsbrac_ type

//Struct type
struct_type         : struct_ lcbrac_ field_decl_list rcbrac_

field_decl_list     : field_decl_list field_decl /* line */
                    | field_decl /* line */

field_decl          : id_list type /*tag
                    | id_list type
                    | anon_field tag
                    | anon_field

tag                 : string_lit_
also not needed
*/
/* apparently not needed
anon_field          : mult_ id_
                    | id_
*/

//Pointer Type
pointer_type        : mult_ type


slice_type          : lsbrac_ rsbrac_ type

func_type           : func_ id_ lrbrac_ func_decl_list  rrbrac_ type

// Statements now!

/* Shift reduce problems right now */
statement_list      : statement_list statement
                    | /* empty */

statement           : decl
                    | simple_stmt
                    | labeled_stmt
                    | return_stmt
                    | break_stmt
                    | goto_stmt
                    | continue_stmt
                    | fallthrough_
                    | defer_ expr
                    | block
                    | if_stmt
                    | for_stmt
                    | switch_stmt

labeled_stmt        : id_ colon_ statement

break_stmt          : break_ id_

simple_stmt         : short_var_decl semi_colon_
                    | expr semi_colon_
                    | inc_dec_stmt semi_colon_
                    | assignment semi_colon_

goto_stmt           : goto_ id_ semi_colon_

continue_stmt       : continue_ id_ semi_colon_

return_stmt         : return_ expr semi_colon_

assignment          : expr_list add_ eq_ expr_list semi_colon_
                    | expr_list mult_ eq_ expr_list semi_colon_

inc_dec_stmt        : expr incre_ semi_colon_
                    | expr decre_ semi_colon_

if_stmt             : if_ simple_stmt line_end expr block else_stmt
                    | if_ expr block else_stmt

else_stmt           : /* empty */
                    | else_ if_stmt
                    | else_ block

for_stmt            : for_ for_clause block
                    | for_ expr block
                    | for_ range_clause block
                    | for_ block

for_clause          : opt_simple_stmt semi_colon_ opt_expr semi_colon_ opt_simple_stmt

range_clause        : range_ expr
                    | expr_list eq_ range_ expr
                    | id_list decla_ range_ expr

opt_expr            : /* empty */
                    | expr

opt_simple_stmt    : /* empty */
                    | simple_stmt

switch_stmt         : expr_switch_stmt
                    | type_switch_stmt


expr_switch_stmt    : switch_ simple_stmt opt_expr lcbrac_ expr_case_clause rcbrac_
                    | switch_ opt_expr lcbrac_ expr_case_clause rcbrac_

expr_case_clause_l  : expr_case_clause_l expr_case_clause
                    | expr_case_clause

expr_case_clause    : case_ expr_list colon_ statement_list
                    | default_ colon_ statement_list


type_switch_stmt    : switch_ opt_simple_stmt type_switch_guard lcbrac_ type_case_clause_l rrbrac_

type_switch_guard   : id_ decla_ primary_expr dot_ lrbrac_ type_ rrbrac_
                    | primary_expr dot_ lrbrac_ type_ rrbrac_

type_case_clause_l  : type_case_clause type_case_clause_l
                    |  //empty

type_case_clause    : type_switch_case colon_ statement_list

type_switch_case    : case_ type_list
                    | default_

type_list           : type_list comma_ type
                    | type

 //So I give up the stuff

expr_list           : rune_lit_

expr                : float_lit_

primary_expr        : string_lit_

operand             : literal
                    | type   //Well it's

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

type_name           : type_primitive
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
