%{
#include <stdio.h>
#include <stdlib.h>
#include "go.tab.c"
#include <errno.h>
#include "memory.h"
#include "treeNode.h"
#include "prettyPrint.h"
#include "type_check.h"
#include "mem_sys.h"

memoryList _treeNodeAllocator = NULL;
nodeAST* _ast;

void _func_throwError(const char * test){

}

size_t _AST_LineNumber = 0;
int line_num = 1;
int char_num = 1;
int switchE = 0;
int counter = 0;
int forE = 0;
char* tokens[3000];
size_t numToken = 0;

int temp;
int prev_token = 0;
%}

decimal_digits	[0-9]
octal_digits	[0-7]
hex_digits		[0-9|A-F|a-f]
letter			[a-b|A-Z]|_

decimal_lit		[1-9][0-9]*
octal_lit		"0"[0-7]*
hex_lit			"0"["x"|"X"][0-9|A-F|a-f]+
int_lit			{decimal_lit}|{octal_lit}|{hex_lit}

decimal  		[0-9]+
exponent		["e"|"E"]["+"|"-"]{decimal}|["e"|"E"]{decimal}
float_lit		{decimal}"."{decimal}|{decimal}"."|{decimal}"."{exponent}|{decimal}"."{decimal}{exponent}|{decimal}{exponent}|"."{decimal}{exponent}|"."{decimal}

string_lit		{interpreted_string_lit}|{raw_string_lit}
raw_string_lit	\`[^`]*\`
interpreted_string_lit	\"([^\\\"\n]|\\.)*\"
rune_lit		(\'.\')|(\'\\.\')

ID				[a-zA-Z_][a-zA-Z0-9_]*
semi_colon		";"
break			"break"
case			"case"
chan			"chan"
const           "const"
continue		"continue"
default			"default"
defer			"defer"
else			"else"
fallthrough		"fallthrough"
for             "for"
func            "func"
go              "go"
goto            "goto"
if              "if"
import          "import"
interface       "interface"
map             "map"
package         "package"
range			"range"
return 			"return"
select 			"select"
struct			"struct"
switch			"switch"
type			"type"
var             "var"
int             "int"
float           "float64"
bool            "bool"
rune            "rune"
string          "string"
print           "print"
println         "println"
append			"append"
add				"+"
minus			"-"
mult			"*"
div				"/"
mod				"%"
amp				"&"
vb				"|"
caret			"^"
ls				"<<"
rs				">>"
unknown 		"&^"
add_eq			"+="
minus_eq		"-="
mult_eq			"*="
div_eq			"/="
mod_eq			"%="
amp_eq			"&="
vb_eq			"|="
caret_eq		"^="
ls_eq			"<<="
rs_eq			">>="
unknown_eq		"&^="
and             "&&"
or				"||"
arrow 			"<-"
incre           "++"
decre			"--"
equality		"=="
lt              "<"
gt              ">"
eq              "="
not             "!"
not_eq          "!="
lteq            "<="
gteq			">="
decla           ":="
etc             "..."
lrbrac			"("
rrbrac			")"
lsbrac			"["
rsbrac			"]"
lcbrac			"{"
rcbrac			"}"
comma			","
dot				"."
colon 			":"
%x REALLYEND

%%
\/\/.*		{
				char_num += strlen(yytext);
			}
\/\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*+\/ {
				for(int i = 0; i < strlen(yytext); i++){
					if(yytext[i] == '\n')line_num++;
				}
				temp = prev_token;
				prev_token = 0;
				switch(temp){
					case int_lit_: return ';';
					case float_lit_: return ';';
			    	case string_lit_: return ';';
			    	case rune_lit_: return ';';
					case int_: return ';';
					case bool_: return ';';
					case float_: return ';';
					case string_: return ';';
					case rune_: return ';';
					case break_: return ';';
					case continue_: return ';';
					case return_: return ';';
					case incre_: return ';';
					case decre_: return ';';
					case ']': return ';';
					case ')': return ';';
					case '}': return ';';
					default: break;
				}
			}
{break}			{prev_token = break_; return break_;}
{case}			{prev_token = case_; return case_;}
{chan}			{prev_token = chan_; return chan_;}
{const}         {prev_token = const_; return const_;}
{continue}		{prev_token = continue_; return continue_;}
{default}		{prev_token = default_; return default_;}
{defer}			{prev_token = defer_; return defer_;}
{else}			{prev_token = else_; return else_;}
{fallthrough}	{prev_token = fallthrough_; return fallthrough_;}
{for}           {prev_token = for_; forE = 1; return for_;}
{func}          {prev_token = func_; return func_;}
{go}            {prev_token = go_; return go_;}
{goto}          {prev_token = goto_; return goto_;}
{if}            {prev_token = if_; return if_;}
{import}        {prev_token = import_; return import_;}
{interface}     {prev_token = interface_; return interface_;}
{map}           {prev_token = map_; return map_;}
{package}       {prev_token = package_; return package_;}
{range}			{prev_token = range_; return range_;}
{return} 		{prev_token = return_; return return_;}
{select} 		{prev_token = select_; return select_;}
{struct}		{prev_token = struct_; return struct_;}
{switch}		{prev_token = switch_; switchE = 1; return switch_;}
{type}			{prev_token = type_; return type_;}
{var}			{prev_token = var_; return var_;}
{int} 	        {prev_token = int_; return int_;}
{float}         {prev_token = float_; return float_;}
{bool}          {prev_token = bool_; return bool_;}
{rune}          {prev_token = rune_; return rune_;}
{string}        {prev_token = string_; return string_;}
{print}         {prev_token = print_; return print_;}
{println}       {prev_token = println_; return println_;}
{append}		{prev_token = append_; return append_;}
{add}			{prev_token = '+'; return '+';}
{minus}			{prev_token = '-'; return '-';}
{mult}			{prev_token = '*'; return '*';}
{div}			{prev_token = '/'; return '/';}
{mod}			{prev_token = '%'; return '%';}
{amp}			{prev_token = '&'; return '&';}
{caret}			{prev_token = '^'; return '^';}
{ls}			{prev_token = ls_; return ls_;}
{rs}			{prev_token = rs_; return rs_;}
{unknown} 		{prev_token = unknown_; return unknown_;}
{add_eq}		{prev_token = add_eq_; return add_eq_;}
{minus_eq}		{prev_token = minus_eq_; return minus_eq_;}
{mult_eq}		{prev_token = mult_eq_; return mult_eq_;}
{div_eq}		{prev_token = div_eq_; return div_eq_;}
{mod_eq}		{prev_token = mod_eq_; return mod_eq_;}
{amp_eq}		{prev_token = amp_eq_; return amp_eq_;}
{vb_eq}			{prev_token = vb_eq_; return vb_eq_;}
{caret_eq}		{prev_token = caret_eq_; return caret_eq_;}
{ls_eq}			{prev_token = ls_eq_; return ls_eq_;}
{rs_eq}			{prev_token = rs_eq_; return rs_eq_;}
{unknown_eq}	{prev_token = unknown_eq_; return unknown_eq_;}
{and}           {prev_token = and_; return and_;}
{or}			{prev_token = or_; return or_;}
{arrow} 		{prev_token = arrow_; return arrow_;}
{incre}         {prev_token = incre_; return incre_;}
{decre}			{prev_token = decre_; return decre_;}
{equality}		{prev_token = equality_; return equality_;}
{lt}            {prev_token = '<'; return '<';}
{gt}            {prev_token = '>'; return '>';}
{eq}            {prev_token = '='; return '=';}
{not}           {prev_token = '!'; return '!';}
{not_eq}        {prev_token = not_eq_; return not_eq_;}
{lteq}          {prev_token = lteq_; return lteq_;}
{gteq}			{prev_token = gteq_; return gteq_;}
{decla}         {prev_token = decla_; return decla_;}
{etc}           {prev_token = etc_; return etc_;}
{lrbrac}		{prev_token = '('; return '(';}
{rrbrac}		{prev_token = ')'; return ')';}
{lsbrac}		{prev_token = '['; return '[';}
{rsbrac}		{prev_token = ']'; return ']';}
{lcbrac}		{
					prev_token = '{';
					return '{';
				}
{rcbrac}		{prev_token = '}'; return '}';}
{comma}			{prev_token = ','; return ',';}
{dot}			{prev_token = '.'; return '.';}
{colon} 		{prev_token = ':'; return ':';}
{vb}			{prev_token = '|'; return '|';}

{rune_lit}		{
					if(yytext[1] == 92 && yytext[2] != 39){
						//printf("Test %d\n", yytext[2]);
						switch(yytext[2]){
							case 'a': yylval.rune_val = 7; break;
							case 'b': yylval.rune_val = 8; break;
							case 'f': yylval.rune_val = 12; break;
							case 'n': yylval.rune_val = 10; break;
							case 'r': yylval.rune_val = 13; break;
							case 't': yylval.rune_val = 9; break;
							case 'v': yylval.rune_val = 11; break;
							case 92: yylval.rune_val = 92; break;
							case 39: yylval.rune_val = 39; break;
						}
					}
					else
						yylval.rune_val = yytext[1];
						prev_token = rune_lit_;
					return rune_lit_;
				}

{int_lit}		{
					int i;
					errno = 0;
					yylval.int_val = strtol(yytext, NULL, 10);
					if(errno == ERANGE){
						errno = 0;
						//Ok check if we can strtof it instead
						yylval.float_val = strtof(yytext, NULL);
						if(errno == ERANGE){
							printf("Error! Integer overflow. Cannot be represented as a float!\nLine[%d], char [%d]\n", line_num, char_num);
							return error_;
						}

						for(i = 0; i < strlen(yytext); i++){
							if(yytext[i] == 'e' || yytext[i] == 'E')
								break;
						}
						if(i >= 16){
							printf("Warning! Rounding error! \nLine[%d], char [%d]\n", line_num, char_num);
						}
						prev_token = int_lit_;
						return float_lit_;
					}
					prev_token = int_lit_;
					return int_lit_;
				}

{float_lit}		{
					int i;
					errno = 0;
					yylval.float_val = strtof(yytext, NULL);
					if(errno == ERANGE){
						printf("Error! Float64 overflow. Cannot be represented as a float!\nLine[%d], char [%d]\n", line_num, char_num);
						return error_;
					}
					for(i = 0; i < strlen(yytext); i++){
						if(yytext[i] == 'e' || yytext[i] == 'E')
							break;
					}
					if(i >= 16){
					    printf("Warning! Rounding error!\nLine[%d], char [%d]\n", line_num, char_num);
					}
					prev_token = int_lit_;
					return float_lit_;
				}
{string_lit}	{
					//printf("String here: %s\n",yytext);
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = string_lit_;
					return string_lit_;
				}

{semi_colon}	{
	                counter ++;
					prev_token = ';';
					return ';';
				}

{ID}			{
					char * val = (char *)malloc(strlen(yytext) + 1);

					//printf("ID here: %s, %d\n", yytext, prev_token);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = id_;
					return id_;
				}

" "|"\t"		{
				char_num++;
				//printf("test\n");
				}

"\n"			{
					if(forE && prev_token == ';'){
						forE = 0;
					}
					if(forE){
						if(prev_token == '{' || prev_token == '}') forE = 0;
						else{
							printf("Error: (line %d), syntax error: missing { after for clause\n", line_num);
							exit(1);
						}
					}
					if(switchE && counter == 2){
						if(prev_token == '{' || prev_token == '}'){
							switchE = 0;
							counter = 0;
						}
						else{
							printf("Error: (line %d), syntax error: missing { after switch clause\n", line_num);
							exit(1);
						}
					}
					counter = 0;
					line_num += 1;
					temp = prev_token;
					prev_token = 0;
					switch(temp){
						case id_: return ';';
						case int_lit_: return ';';
						case float_lit_: return ';';
						case string_lit_: return ';';
						case rune_lit_: return ';';
						case int_: return ';';
						case bool_: return ';';
						case float_: return ';';
						case string_: return ';';
						case rune_: return ';';
						case break_: return ';';
						case continue_: return ';';
						case return_: return ';';
						case incre_: return ';';
						case decre_: return ';';
						case ']': return ';';
						case ')': return ';';
						case '}': return ';';
						default: break;
					}
				}
(.)				{
					return error_;
				}

<INITIAL><<EOF>>        {
							BEGIN(REALLYEND);
							switch(prev_token){
								case id_: return ';';
								case int_lit_: return ';';
								case float_lit_: return ';';
								case string_lit_: return ';';
								case rune_lit_: return ';';
								case int_: return ';';
								case bool_: return ';';
								case float_: return ';';
								case string_: return ';';
								case rune_: return ';';
								case break_: return ';';
								case continue_: return ';';
								case return_: return ';';
								case incre_: return ';';
								case decre_: return ';';
								case ']': return ';';
								case ')': return ';';
								case '}': return ';';
							default: break;
							}
						}

<REALLYEND><<EOF>>      { return 0; }
%%

int main(int argc, char ** argv){
	FILE * stream = stdout;
	_treeNodeAllocator = newMemoryList();
	yyparse();


	if(argc == 2){
		stream = fopen(argv[1], "w+");
		if(stream == NULL){
			stream = stdout;
		}
	 }

	prettyPrint(_ast, stream);
	type_check_prog(_ast);
}
