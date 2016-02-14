%{
#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>

extern char *yytext; /* string from scanner */
extern int line_num;
extern int line_char;

void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", line_num, s); }
int yylex(void);
union value{
  int     int_val;
  float   float_val;
  char *  str_val;
};

%}


%union{ //This is for clarity
  int   int_val;
  float   float_val;
  char *  str_val;
  struct node * node_val;
}


%token error_
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
%token '+'
%token '-'
%token '*'
%token '/'
%token '%'
%token '&'
%token '^'
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
%token '<'
%token '>'
%token '='
%token '!'
%token not_eq_
%token lteq_
%token gteq_
%token decla_
%token etc_
%token ']'
%token '['
%token '}'
%token '{'
%token '('
%token ')'
%token ','
%token '.'
%token ':'
%token '|'
%token int_lit_
%token float_lit_
%token string_lit_
%token rune_lit_
%token ';'
%token id_
%token unary

%left or_
%left and_
%left equality_ not_eq_ '<' '>' lteq_ gteq_
%left '+' '-' '|' '^'
%left '*' '/' '%' ls_ rs_ '&' unknown_
%left unary

%error-verbose
%locations
%%

//A go program is composed of a package declaration and multiple top_level declarations


go_prog             : pckg_decl ';' top_decl_list

pckg_decl           : package_ id_


top_decl_list       : top_decl_list top_decl
                    |

top_decl            : decl | func_decl

decl                : var_decl | type_decl

func_decl           : func_ func_name function
                    | func_ func_name signature

func_name           : id_

function            : signature func_body

func_body           : block

block               : block_tmp ';'

block_tmp           :'{' stmt_list '}'

signature           : params
                    | params result

result              : type

params              : '(' ')'
                    | '(' params_list ')'

params_list         : params_list ',' params_decl | params_decl

params_decl         : id_list type

var_decl            : var_ var_spec ';'
                    | var_ '('  var_spec_list ')'  ';'  //万恶之源 ；

type_decl           : type_ type_spec ';'
                    | type_ '(' type_spec_list ')' ';'

type_spec_list      : type_spec_list type_spec ';'
                    |

type_spec           : id_ type

var_spec_list       : var_spec_list var_spec ';'
                    |

var_spec            : id_list '=' expr_list
                    | id_list type '=' expr_list
                    | id_list type

id_list             : id_
                    | id_list ',' id_

type                : basic_type | '[' ']' type | struct_ '{' field_decl_list '}' | '[' int_lit_ ']' type | id_

basic_type          : int_ | float_ | string_ | rune_ | bool_

field_decl_list     : field_decl_list field_decl
                    |

field_decl          : id_list type

//end Function declaration
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// statements
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

stmt_list           : stmt_list  stmt
                    |

stmt                : decl
                    | block
                    | print_stmt
                    | println_stmt
                    | return_stmt
                    | if_stmt
                    | simple_stmt
                    | switch_stmt
                    | for_stmt
                    | break_stmt
                    | cont_stmt

simple_stmt         : simple_stmt_v ';'

simple_stmt_v       : expr_stmt
                    | inc_stmt
                    | dec_stmt
                    | assign_stmt
                    | short_decl
                    |

assign_stmt         : expr_list '=' expr_list
                    | expr assign_op expr

short_decl          : expr_list decla_ expr_list

inc_stmt            : expr incre_

dec_stmt            : expr decre_

print_stmt          : print_ '(' expr_list ')' ';'
                    | print_ '(' ')' ';'

println_stmt        : println_ '(' expr_list ')' ';'
                    | println_ '(' ')' ';'

return_stmt         : return_ expr ';'
                    | return_ ';'


if_stmt             : if_ if_cond block
                    | if_ if_cond block else_ else_block

switch_stmt         : switch_ switch_cond '{' case_clause_list '}'

for_stmt            : for_ for_clause block

for_clause          : condition | for_stmt_clause

condition           : expr
                    |

for_stmt_clause     : simple_stmt_v ';' condition ';' simple_stmt_v

switch_cond         : simple_stmt ';' expr
                    | simple_stmt ';'
                    | expr
                    |

case_clause_list    : case_clause_list case_clause
                    |

case_clause         : switch_case ':' stmt_list

switch_case         : case_ expr_list
                    | default_

if_cond             : expr
                    | simple_stmt expr

else_block          : block
                    | if_stmt

break_stmt          : break_ ';'

cont_stmt           : continue_ ';'

assign_op           : add_eq_ | minus_eq_ | mult_eq_ | div_eq_ | mod_eq_ | amp_eq_ | vb_eq_ | caret_eq_ | ls_eq_ | rs_eq_ | unknown_eq_

expr_stmt           : expr

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//expressions done
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

expr_list           : expr
                    | expr_list ',' expr

operand             : '(' expr ')'
                    | operand_name
                    | literal;

operand_name        : id_

literal             : int_lit_
                    | float_lit_
                    | string_lit_
                    | rune_lit_

expr                : primary_expr
                    | expr '*' expr
                    | expr '/' expr
                    | expr '%' expr
                    | expr '&' expr
                    | expr unknown_ expr
                    | expr ls_ expr
                    | expr rs_ expr
                    | expr '|' expr
                    | expr '^' expr
                    | expr '-' expr
                    | expr '+' expr
                    | expr equality_ expr
                    | expr '<' expr
                    | expr '>' expr
                    | expr lteq_ expr
                    | expr gteq_ expr
                    | expr not_eq_ expr
                    | expr and_ expr
                    | expr or_ expr
                    | append
                    | unary_op expr %prec unary

unary_op            : '+' | '-' | '^' | '!'

func_call           : primary_expr '(' expr_list ')'
                    | primary_expr '(' ')'

append              : append_ '(' id_ ',' expr_list ')'

primary_expr        : operand
                    | func_call
                    | type_cast
                    | primary_expr selector
                    | primary_expr index
                    | primary_expr slice

selector            : '.' id_

type_cast           : basic_type '(' expr ')'

index               : '[' expr ']'

slice               : '[' expr ':' expr ']'
                    | '[' expr ':'  ']'
                    | '['  ':' expr ']'
                    | '['  ':'  ']'
                    | '[' expr ':' expr ':' expr ']'
                    | '['  ':' expr ':' expr ']'
%%
