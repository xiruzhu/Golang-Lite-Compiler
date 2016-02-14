%{
#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>
#include "treeNode.h"

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
  char rune_val;
  struct nodeAST* node_val;
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

%type <node_val> expr_list operand operand_name literal expr func_call primary_expr type_cast slice basic_type
%type <node_val> inc_stmt dec_stmt print_stmt println_stmt return_stmt stmt_list simple_stmt_v simple_stmt stmt assign_stmt
%type <rune_val>  rune_lit_
%type <string_val> string_lit_ id_
%type <int_val> int_lit_
%type <float_val> float_lit_
%%

//A go program is composed of a package declaration and multiple top_level declarations


go_prog             : pckg_decl ';' top_decl_list

pckg_decl           : package_ id_


top_decl_list       : top_decl_list top_decl
                    |

top_decl            : decl 
                    | func_decl

decl                : var_decl 
                    | type_decl

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

params_list         : params_list ',' params_decl 
                    | params_decl

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

type                : basic_type 
                    | '[' ']' type 
                    | struct_ '{' field_decl_list '}' 
                    | '[' int_lit_ ']' type 
                    | id_

basic_type          : int_                                        {$$ = newBasicTypeInt();}
                    | float_                                      {$$ = newBasicTypeFloat();}
                    | string_                                     {$$ = newBasicTypeString();}
                    | rune_                                       {$$ = newBasicTypeRune();}
                    | bool_                                       {$$ = newBasicTypeBool();}

field_decl_list     : field_decl_list field_decl
                    |

field_decl          : id_list type

//end Function declaration
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// statements
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

stmt_list           : stmt  stmt_list                             {$$ = newStateList($1, $2);}
                    |                                             {$$ = NULL;}

stmt                : decl                                        {$$ = NULL;}
                    | block                                       {$$ = NULL;}
                    | print_stmt                                  {$$ = $1;}
                    | println_stmt                                {$$ = $1;}
                    | return_stmt                                 {$$ = $1;}
                    | if_stmt                                     {$$ = NULL;}
                    | simple_stmt                                 {$$ = $1;}
                    | switch_stmt                                 {$$ = NULL;}
                    | for_stmt                                    {$$ = NULL;}
                    | break_stmt                                  {$$ = NULL;}
                    | cont_stmt                                   {$$ = NULL;}

simple_stmt         : simple_stmt_v ';'                           {$$ = $1;}

simple_stmt_v       : expr                                        {$$ = $1;}
                    | inc_stmt                                    {$$ = $1;}
                    | dec_stmt                                    {$$ = $1;}
                    | assign_stmt                                 {$$ = $1;}
                    | short_decl                                  {$$ = NULL;}
                    |                                             {$$ = NULL;}

assign_stmt         : expr_list '=' expr_list                     {$$ = newAssign($1, $3);}
                    | expr add_eq_ expr                           {$$ = newAssignAdd($1, $3);}
                    | expr minus_eq_ expr                         {$$ = newAssignSub($1, $3);}
                    | expr mult_eq_ expr                          {$$ = newAssignMul($1, $3);}
                    | expr div_eq_ expr                           {$$ = newAssignDiv($1, $3);}
                    | expr mod_eq_ expr                           {$$ = newAssignMod($1, $3);}
                    | expr amp_eq_ expr                           {$$ = newAssignAnd($1, $3);}
                    | expr vb_eq_ expr                            {$$ = newAssignOr($1, $3);}
                    | expr caret_eq_ expr                         {$$ = newAssignXor($1, $3);} 
                    | expr ls_eq_ expr                            {$$ = newAssignShiftLeft($1, $3);}
                    | expr rs_eq_ expr                            {$$ = newAssignShiftRight($1, $3);}
                    | expr unknown_eq_ expr                       {$$ = newAssignAndNot($1, $3);}

short_decl          : expr_list decla_ expr_list

inc_stmt            : expr incre_                                 {$$ = newInc($1);}

dec_stmt            : expr decre_                                 {$$ = newDec($1);}

print_stmt          : print_ '(' expr_list ')' ';'                {$$ = newPrint($3);}
                    | print_ '(' ')' ';'                          {$$ = newPrint(NULL);}

println_stmt        : println_ '(' expr_list ')' ';'              {$$ = newPrintln($3);}
                    | println_ '(' ')' ';'                        {$$ = newPrintln(NULL);}

return_stmt         : return_ expr ';'                            {$$ = newRetrun($2);}
                    | return_ ';'                                 {$$ = newReturn(NULL);}


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

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//expressions done
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

expr_list           : expr                                        {$$ = newExprList($1, NULL);}
                    | expr ',' expr_list                          {$$ = newExprList()}

operand             : '(' expr ')'                                {$$ = $2;}
                    | operand_name                                {$$ = $1;}
                    | literal                                     {$$ = $1;}

operand_name        : id_                                         {$$ = newIdentifier($1);}

literal             : int_lit_                                    {$$ = newLiteralInt($1);}
                    | float_lit_                                  {$$ = newLiteralFloat($1);}
                    | string_lit_                                 {$$ = newLiteralString($1);}
                    | rune_lit_                                   {$$ = newLiteralRune($1);}

expr                : primary_expr                                {$$ = $1;}
                    | expr '*' expr                               {$$ = newMul($1, $3);}
                    | expr '/' expr                               {$$ = newDiv($1, $3);}
                    | expr '%' expr                               {$$ = newMod($1, $3);}
                    | expr '&' expr                               {$$ = newBitAnd($1, $3);}
                    | expr unknown_ expr                          {$$ = newBitAndNot($1, $3);}
                    | expr ls_ expr                               {$$ = newShiftLeft($1, $3);}
                    | expr rs_ expr                               {$$ = newShiftRight($1, $3);}
                    | expr '|' expr                               {$$ = newBitOr($1, $3);}
                    | expr '^' expr                               {$$ = newBitNot($1, $3);}
                    | expr '-' expr                               {$$ = newSub($1, $3);}
                    | expr '+' expr                               {$$ = newAdd($1, $3);}
                    | expr equality_ expr                         {$$ = newEqual($1, $3);}
                    | expr '<' expr                               {$$ = newLess($1, $3);}
                    | expr '>' expr                               {$$ = newGreat($1, $3);}
                    | expr lteq_ expr                             {$$ = newLessEqual($1, $3);}
                    | expr gteq_ expr                             {$$ = newGreatEqual($1, $3);}
                    | expr not_eq_ expr                           {$$ = newNotEqual($1, $3);}
                    | expr and_ expr                              {$$ = newLogicAnd($1, $3);}
                    | expr or_ expr                               {$$ = newLogicOr($1, $3);}
                    | append_ '(' id_ ',' expr_list ')'           {$$ = newAppend($3, $5);}
                    | '+' expr         %prec unary                {$$ = newPos($2);}
                    | '-' expr         %prec unary                {$$ = newNeg($2);}
                    | '^' expr         %prec unary                {$$ = newBitNot($2);}
                    | '!' expr         %prec unary                {$$ = newNot($2);}

func_call           : primary_expr '(' expr_list ')'              {$$ = newFuncCall($1, $3);}
                    | primary_expr '(' ')'                        {$$ = newFuncCall($1, NULL);}

primary_expr        : operand                                     {$$ = $1;}
                    | func_call                                   {$$ = $1;}
                    | type_cast                                   {$$ = $1;}    //TODO weeding
                    | primary_expr '[' expr ']'                   {$$ = newSelector($1, $3);}
                    | primary_expr '.' id_                        {$$ = newIndex($1, $3);}
                    | primary_expr slice                          {$$ = newSlice($1, $2);}

type_cast           : basic_type '(' expr ')'                     {$$ = newCast($1, $3);}

slice               : '[' expr ':' expr ']'                       {$$ = newAddressSlice($2, $4);}
                    | '[' expr ':'  ']'                           {$$ = newAddressSlice($2, NULL);}
                    | '['  ':' expr ']'                           {$$ = newAddressSlice(NULL, $3);}
                    | '['  ':'  ']'                               {$$ = newAddressSlice(NULL, NULL);}
                    | '[' expr ':' expr ':' expr ']'              {$$ = newAddressSliceFull($2, $4, $6);}
                    | '['  ':' expr ':' expr ']'                  {$$ = newAddressSliceFull(NULL, $3, $5);}
%%
