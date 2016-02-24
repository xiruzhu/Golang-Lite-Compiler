%{
#include <stdio.h> /* for printf */
#include <stdlib.h>
#include <string.h>
#include "treeNode.h"
#include "memory.h"

extern char *yytext; /* string from scanner */
extern int line_num;
extern int line_char;
extern memoryList _treeNodeAllocator;

void yyerror(char const *s) {fprintf(stderr, "Error: (line %d) %s\n", line_num, s); }
int yylex(void);
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

%type <node_val> expr_list operand operand_name literal expr func_call primary_expr type_cast slice
%type <node_val> stmt_list stmt simple_stmt simple_stmt_v assign_stmt short_decl print_stmt println_stmt return_stmt if_stmt switch_stmt for_stmt for_clause condition for_stmt_clause switch_cond case_clause_list case_clause if_cond else_block
%type <node_val> block basic_type go_prog pckg_decl top_decl_list top_decl params params_list params_decl var_decl type_decl type_spec_list type_spec var_spec_list var_spec id_list type field_decl_list field_decl
%type <rune_val>  rune_lit_
%type <str_val> string_lit_ id_
%type <int_val> int_lit_
%type <float_val> float_lit_
%%

//A go program is composed of a package declaration and multiple top_level declarations
go_prog             : pckg_decl ';' top_decl_list                 {$$ = newProgram($1, $3, _treeNodeAllocator);}

pckg_decl           : package_ id_                                {$$ = newPackage(newIdentifier($2, _treeNodeAllocator), _treeNodeAllocator);}

top_decl_list       : top_decl top_decl_list                      {$$ = newProgList($1, $2, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

top_decl            : var_decl 
                    | type_decl
                    | func_ id_ params block                      {$$ = newFunction(newIdentifier($2, _treeNodeAllocator), $3, NULL, $4, _treeNodeAllocator);}
					| func_ id_ params type block                 {$$ = newFunction(newIdentifier($2, _treeNodeAllocator), $3, $4, $5, _treeNodeAllocator);}
                    | func_ id_ params                            {$$ = newFunction(newIdentifier($2, _treeNodeAllocator), $3, NULL, NULL, _treeNodeAllocator);}
					| func_ id_ params type                       {$$ = newFunction(newIdentifier($2, _treeNodeAllocator), $3, $4, NULL, _treeNodeAllocator);}

block               : '{' stmt_list '}' ';'                       {$$ = $2;}

params              : '(' ')'                                     {$$ = NULL;}
                    | '(' params_list ')'                         {$$ = $2;}
					
params_list         : params_decl ',' params_list                 {$$ = newParameterList($1, $3, _treeNodeAllocator);}  
                    | params_decl                                 {$$ = newParameterList($1, NULL, _treeNodeAllocator);}

params_decl         : id_list type                                {$$ = newParameter($1, $2, _treeNodeAllocator);}

var_decl            : var_ var_spec ';'                           {$$ = newVarDeclareList($2, NULL, _treeNodeAllocator);}
                    | var_ '('  var_spec_list ')'  ';'            {$$ = $3;}

type_decl           : type_ type_spec ';'                         {$$ = newTypeDeclareList($2, NULL, _treeNodeAllocator);}
                    | type_ '(' type_spec_list ')' ';'            {$$ = $3;}

type_spec_list      : type_spec ';' type_spec_list                {$$ = newTypeDeclareList($1, $3, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

type_spec           : id_ type                                    {$$ = newTypeDeclare(newIdentifier($1, _treeNodeAllocator), $2, _treeNodeAllocator);}

var_spec_list       : var_spec  ';' var_spec_list                 {$$ = newVarDeclareList($1, $3, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

var_spec            : id_list '=' expr_list                       {$$ = newVarDeclare($1, $3, NULL, _treeNodeAllocator);}
                    | id_list type '=' expr_list                  {$$ = newVarDeclare($1, $4, $2, _treeNodeAllocator);}
                    | id_list type                                {$$ = newVarDeclare($1, NULL, $2, _treeNodeAllocator);}

id_list             : id_                                         {$$ = newIdentifierList(newIdentifier($1, _treeNodeAllocator), NULL, _treeNodeAllocator);}
                    | id_ ',' id_list                             {$$ = newIdentifierList(newIdentifier($1, _treeNodeAllocator), $3, _treeNodeAllocator);}
					
type                : basic_type                                  {$$ = $1;}
                    | '[' ']' type                                {$$ = newSliceType($3, _treeNodeAllocator);}
                    | struct_ '{' field_decl_list '}'             {$$ = newStruct($3, _treeNodeAllocator);}
                    | '[' int_lit_ ']' type                       {$$ = newArrayType(newLiteralInt($2, _treeNodeAllocator), $4, _treeNodeAllocator);}
                    | id_                                         {$$ = newIdentifier($1, _treeNodeAllocator);}

basic_type          : int_                                        {$$ = newBasicTypeInt(_treeNodeAllocator);}
                    | float_                                      {$$ = newBasicTypeFloat(_treeNodeAllocator);}
                    | string_                                     {$$ = newBasicTypeString(_treeNodeAllocator);}
                    | rune_                                       {$$ = newBasicTypeRune(_treeNodeAllocator);}
                    | bool_                                       {$$ = newBasicTypeBool(_treeNodeAllocator);}

field_decl_list     : field_decl field_decl_list                  {$$ = newStructDecList($1, $2, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

field_decl          : id_list type                                {$$ = newStructDeclare($1, $2, _treeNodeAllocator);}

//end Function declaration
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// statements
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

stmt_list           : stmt  stmt_list                             {$$ = newStateList($1, $2, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

stmt                : var_decl                                    {$$ = $1;}  
                    | type_decl                                   {$$ = $1;}  
                    | block                                       {$$ = $1;}
                    | print_stmt                                  {$$ = $1;}
                    | println_stmt                                {$$ = $1;}
                    | return_stmt                                 {$$ = $1;}
                    | if_stmt                                     {$$ = $1;}
                    | simple_stmt                                 {$$ = $1;}
                    | switch_stmt                                 {$$ = $1;}
                    | for_stmt                                    {$$ = $1;}
                    | break_ ';'                                  {$$ = newControlBreak(_treeNodeAllocator);}
                    | continue_ ';'                               {$$ = newControlContinue(_treeNodeAllocator);}

simple_stmt         : simple_stmt_v ';'                           {$$ = $1;}

simple_stmt_v       : expr                                        {$$ = $1;}
                    | expr incre_                                 {$$ = newInc($1, _treeNodeAllocator);}
                    | expr decre_                                 {$$ = newDec($1, _treeNodeAllocator);}
                    | assign_stmt                                 {$$ = $1;}
                    | short_decl                                  {$$ = $1;}
                    |                                             {$$ = NULL;}

assign_stmt         : expr_list '=' expr_list                     {$$ = newAssign($1, $3, _treeNodeAllocator);}
                    | expr add_eq_ expr                           {$$ = newAssignAdd($1, $3, _treeNodeAllocator);}
                    | expr minus_eq_ expr                         {$$ = newAssignSub($1, $3, _treeNodeAllocator);}
                    | expr mult_eq_ expr                          {$$ = newAssignMul($1, $3, _treeNodeAllocator);}
                    | expr div_eq_ expr                           {$$ = newAssignDiv($1, $3, _treeNodeAllocator);}
                    | expr mod_eq_ expr                           {$$ = newAssignMod($1, $3, _treeNodeAllocator);}
                    | expr amp_eq_ expr                           {$$ = newAssignAnd($1, $3, _treeNodeAllocator);}
                    | expr vb_eq_ expr                            {$$ = newAssignOr($1, $3, _treeNodeAllocator);}
                    | expr caret_eq_ expr                         {$$ = newAssignXor($1, $3, _treeNodeAllocator);} 
                    | expr ls_eq_ expr                            {$$ = newAssignShiftLeft($1, $3, _treeNodeAllocator);}
                    | expr rs_eq_ expr                            {$$ = newAssignShiftRight($1, $3, _treeNodeAllocator);}
                    | expr unknown_eq_ expr                       {$$ = newAssignAndNot($1, $3, _treeNodeAllocator);}

short_decl          : expr_list decla_ expr_list                  {$$ = newShortDeclare($1, $3, _treeNodeAllocator);}

print_stmt          : print_ '(' expr_list ')' ';'                {$$ = newPrint($3, _treeNodeAllocator);}
                    | print_ '(' ')' ';'                          {$$ = newPrint(NULL, _treeNodeAllocator);}

println_stmt        : println_ '(' expr_list ')' ';'              {$$ = newPrintln($3, _treeNodeAllocator);}
                    | println_ '(' ')' ';'                        {$$ = newPrintln(NULL, _treeNodeAllocator);}

return_stmt         : return_ expr ';'                            {$$ = newReturn($2, _treeNodeAllocator);}
                    | return_ ';'                                 {$$ = newReturn(NULL, _treeNodeAllocator);}

if_stmt             : if_ if_cond block                           {$$ = newIfBlock($2, $3, _treeNodeAllocator);}
                    | if_ if_cond block else_ else_block          {$$ = newIfElseBlock($2, $3, $5, _treeNodeAllocator);}

switch_stmt         : switch_ switch_cond '{' case_clause_list '}'{$$ = newSwitchBlock($2, $4, _treeNodeAllocator);}

for_stmt            : for_ for_clause block                       {$$ = newForBlock($2, $3, _treeNodeAllocator);}

for_clause          : condition                                   {$$ = $1;}
	                | for_stmt_clause                             {$$ = $1;}

condition           : expr                                        {$$ = $1;}
                    |                                             {$$ = NULL;}

for_stmt_clause     : simple_stmt_v ';' condition ';' simple_stmt_v {$$ = newForCluase($1, $3, $5, _treeNodeAllocator);}

switch_cond         : simple_stmt  expr                           {$$ = newSwitchCondition($1, $2, _treeNodeAllocator);}
                    | simple_stmt                                 {$$ = newSwitchCondition($1, NULL, _treeNodeAllocator);}
                    | expr                                        {$$ = newSwitchCondition(NULL, $1, _treeNodeAllocator);}
                    |                                             {$$ = newSwitchCondition(NULL, NULL, _treeNodeAllocator);}

case_clause_list    : case_clause case_clause_list                {$$ = newCaseList($1, $2, _treeNodeAllocator);}
                    |                                             {$$ = NULL;}

case_clause         : case_ expr_list ':' stmt_list               {$$ = newCaseClause($2, $4, _treeNodeAllocator);}
					| default_ ':' stmt_list                      {$$ = newCaseClause(NULL, $3, _treeNodeAllocator);}

if_cond             : expr                                        {$$ = newIfCondition(NULL, $1, _treeNodeAllocator);}
                    | simple_stmt expr                            {$$ = newIfCondition($1, $2, _treeNodeAllocator);}

else_block          : block                                       {$$ = $1;}
                    | if_stmt                                     {$$ = $1;}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//expressions done
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

expr_list           : expr                                        {$$ = newExprList($1, NULL, _treeNodeAllocator);}
                    | expr ',' expr_list                          {$$ = newExprList($1, $3, _treeNodeAllocator);}

operand             : '(' expr ')'                                {$$ = $2;}
                    | operand_name                                {$$ = $1;}
                    | literal                                     {$$ = $1;}

operand_name        : id_                                         {$$ = newIdentifier($1, _treeNodeAllocator);}

literal             : int_lit_                                    {$$ = newLiteralInt($1, _treeNodeAllocator);}
                    | float_lit_                                  {$$ = newLiteralFloat($1, _treeNodeAllocator);}
                    | string_lit_                                 {$$ = newLiteralString($1, _treeNodeAllocator);}
                    | rune_lit_                                   {$$ = newLiteralRune($1, _treeNodeAllocator);}

expr                : primary_expr                                {$$ = $1;}
                    | expr '*' expr                               {$$ = newMul($1, $3, _treeNodeAllocator);}
                    | expr '/' expr                               {$$ = newDiv($1, $3, _treeNodeAllocator);}
                    | expr '%' expr                               {$$ = newMod($1, $3, _treeNodeAllocator);}
                    | expr '&' expr                               {$$ = newBitAnd($1, $3, _treeNodeAllocator);}
                    | expr unknown_ expr                          {$$ = newBitAndNot($1, $3, _treeNodeAllocator);}
                    | expr ls_ expr                               {$$ = newShiftLeft($1, $3, _treeNodeAllocator);}
                    | expr rs_ expr                               {$$ = newShiftRight($1, $3, _treeNodeAllocator);}
                    | expr '|' expr                               {$$ = newBitOr($1, $3, _treeNodeAllocator);}
                    | expr '^' expr                               {$$ = newBitXor($1, $3, _treeNodeAllocator);}
                    | expr '-' expr                               {$$ = newSub($1, $3, _treeNodeAllocator);}
                    | expr '+' expr                               {$$ = newAdd($1, $3, _treeNodeAllocator);}
                    | expr equality_ expr                         {$$ = newEqual($1, $3, _treeNodeAllocator);}
                    | expr '<' expr                               {$$ = newLess($1, $3, _treeNodeAllocator);}
                    | expr '>' expr                               {$$ = newGreat($1, $3, _treeNodeAllocator);}
                    | expr lteq_ expr                             {$$ = newLessEqual($1, $3, _treeNodeAllocator);}
                    | expr gteq_ expr                             {$$ = newGreatEqual($1, $3, _treeNodeAllocator);}
                    | expr not_eq_ expr                           {$$ = newNotEqual($1, $3, _treeNodeAllocator);}
                    | expr and_ expr                              {$$ = newLogicAnd($1, $3, _treeNodeAllocator);}
                    | expr or_ expr                               {$$ = newLogicOr($1, $3, _treeNodeAllocator);}
                    | append_ '(' id_ ',' expr_list ')'           {$$ = newAppend(newIdentifier($3, _treeNodeAllocator), $5, _treeNodeAllocator);}
                    | '+' expr         %prec unary                {$$ = newPos($2, _treeNodeAllocator);}
                    | '-' expr         %prec unary                {$$ = newNeg($2, _treeNodeAllocator);}
                    | '^' expr         %prec unary                {$$ = newBitNot($2, _treeNodeAllocator);}
                    | '!' expr         %prec unary                {$$ = newLogicNot($2, _treeNodeAllocator);}

func_call           : primary_expr '(' expr_list ')'              {$$ = newFuncCall($1, $3, _treeNodeAllocator);}
                    | primary_expr '(' ')'                        {$$ = newFuncCall($1, NULL, _treeNodeAllocator);}

primary_expr        : operand                                     {$$ = $1;}
                    | func_call                                   {$$ = $1;}
                    | type_cast                                   {$$ = $1;}    //TODO weeding
                    | primary_expr '[' expr ']'                   {$$ = newSelector($1, $3, _treeNodeAllocator);}
                    | primary_expr '.' id_                        {$$ = newIndex($1, newIdentifier($3, _treeNodeAllocator), _treeNodeAllocator);}
                    | primary_expr slice                          {$$ = newSlice($1, $2, _treeNodeAllocator);}

type_cast           : basic_type '(' expr ')'                     {$$ = newCast($1, $3, _treeNodeAllocator);}

slice               : '[' expr ':' expr ']'                       {$$ = newAddressSlice($2, $4, _treeNodeAllocator);}
                    | '[' expr ':'  ']'                           {$$ = newAddressSlice($2, NULL, _treeNodeAllocator);}
                    | '['  ':' expr ']'                           {$$ = newAddressSlice(NULL, $3, _treeNodeAllocator);}
                    | '['  ':'  ']'                               {$$ = newAddressSlice(NULL, NULL, _treeNodeAllocator);}
                    | '[' expr ':' expr ':' expr ']'              {$$ = newAddressSliceFull($2, $4, $6, _treeNodeAllocator);}
                    | '['  ':' expr ':' expr ']'                  {$$ = newAddressSliceFull(NULL, $3, $5, _treeNodeAllocator);}
%%
