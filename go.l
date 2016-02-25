%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int line_num = 1;
int char_num = 1;

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
float_lit		{decimal}"."{decimal}|{decimal}"."{exponent}|{decimal}"."{decimal}{exponent}|{decimal}{exponent}|"."{decimal}{exponent}|"."{decimal}

string_lit		{interpreted_string_lit}|{raw_string_lit}
raw_string_lit	\`[^`]*\`
interpreted_string_lit	\"(\\.|[^(\\")])*\"
rune_lit		(\'.\')|(\'\\.\')

ID				[a-z|A-Z][a-z|A-Z|0-9|"_"]*
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
vb				'|'
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
"//".*		{
				printf("Eating ...%s\n", yytext);
				char_num += strlen(yytext);
			}

\/\*([^\*]|\*+^\/)*\*\/ {
			printf("Eating ...%s\n", yytext);
			for(int i = 0; i < strlen(yytext); i++)
				if(yytext[i] == '\n')
					line_num++;
			}
{break}			{printf("%s\n", yytext); prev_token = break_; return break_;}
{case}			{printf("%s\n", yytext); prev_token = case_; return case_;}
{chan}			{printf("%s\n", yytext); prev_token = chan_; return chan_;}
{const}         {printf("%s\n", yytext); prev_token = const_; return const_;}
{continue}		{printf("%s\n", yytext); prev_token = continue_; return continue_;}
{default}		{printf("%s\n", yytext); prev_token = default_; return default_;}
{defer}			{printf("%s\n", yytext); prev_token = defer_; return defer_;}
{else}			{printf("%s\n", yytext); prev_token = else_; return else_;}
{fallthrough}	{printf("%s\n", yytext); prev_token = fallthrough_; return fallthrough_;}
{for}           {printf("%s\n", yytext); prev_token = for_; return for_;}
{func}          {printf("%s\n", yytext); prev_token = func_; return func_;}
{go}            {printf("%s\n", yytext); prev_token = go_; return go_;}
{goto}          {printf("%s\n", yytext); prev_token = goto_; return goto_;}
{if}            {printf("%s\n", yytext); prev_token = if_; return if_;}
{import}        {printf("%s\n", yytext); prev_token = import_; return import_;}
{interface}     {printf("%s\n", yytext); prev_token = interface_; return interface_;}
{map}           {printf("%s\n", yytext); prev_token = map_; return map_;}
{package}       {printf("%s\n", yytext); prev_token = package_; return package_;}
{range}			{printf("%s\n", yytext); prev_token = range_; return range_;}
{return} 		{printf("%s\n", yytext); prev_token = return_; return return_;}
{select} 		{printf("%s\n", yytext); prev_token = select_; return select_;}
{struct}		{printf("%s\n", yytext); prev_token = struct_; return struct_;}
{switch}		{printf("%s\n", yytext); prev_token = switch_; return switch_;}
{type}			{printf("%s\n", yytext); prev_token = type_; return type_;}
{var}			{printf("%s\n", yytext); prev_token = var_; return var_;}
{int} 	        {printf("%s\n", yytext); prev_token = int_; return int_;}
{float}         {printf("%s\n", yytext); prev_token = float_; return float_;}
{bool}          {printf("%s\n", yytext); prev_token = bool_; return bool_;}
{rune}          {printf("%s\n", yytext); prev_token = rune_; return rune_;}
{string}        {printf("%s\n", yytext); prev_token = string_; return string_;}
{print}         {printf("%s\n", yytext); prev_token = print_; return print_;}
{println}       {printf("%s\n", yytext); prev_token = println_; return println_;}
{append}		{printf("%s\n", yytext); prev_token = append_; return append_;}
{add}			{printf("%s\n", yytext); prev_token = '+'; return '+';}
{minus}			{printf("%s\n", yytext); prev_token = '-'; return '-';}
{mult}			{printf("%s\n", yytext); prev_token = '*'; return '*';}
{div}			{printf("%s\n", yytext); prev_token = '/'; return '/';}
{mod}			{printf("%s\n", yytext); prev_token = '*'; return '*';}
{amp}			{printf("%s\n", yytext); prev_token = '&'; return '&';}
{caret}			{printf("%s\n", yytext); prev_token = '^'; return '^';}
{ls}			{printf("%s\n", yytext); prev_token = ls_; return ls_;}
{rs}			{printf("%s\n", yytext); prev_token = rs_; return rs_;}
{unknown} 		{printf("%s\n", yytext); prev_token = unknown_; return unknown_;}
{add_eq}		{printf("%s\n", yytext); prev_token = add_eq_; return add_eq_;}
{minus_eq}		{printf("%s\n", yytext); prev_token = minus_eq_; return minus_eq_;}
{mult_eq}		{printf("%s\n", yytext); prev_token = mult_eq_; return mult_eq_;}
{div_eq}		{printf("%s\n", yytext); prev_token = div_eq_; return div_eq_;}
{mod_eq}		{printf("%s\n", yytext); prev_token = mod_eq_; return mod_eq_;}
{amp_eq}		{printf("%s\n", yytext); prev_token = amp_eq_; return amp_eq_;}
{vb_eq}			{printf("%s\n", yytext); prev_token = vb_eq_; return vb_eq_;}
{caret_eq}		{printf("%s\n", yytext); prev_token = caret_eq_; return caret_eq_;}
{ls_eq}			{printf("%s\n", yytext); prev_token = ls_eq_; return ls_eq_;}
{rs_eq}			{printf("%s\n", yytext); prev_token = rs_eq_; return rs_eq_;}
{unknown_eq}	{printf("%s\n", yytext); prev_token = unknown_eq_; return unknown_eq_;}
{and}           {printf("%s\n", yytext); prev_token = and_; return and_;}
{or}			{printf("%s\n", yytext); prev_token = or_; return or_;}
{arrow} 		{printf("%s\n", yytext); prev_token = arrow_; return arrow_;}
{incre}         {printf("%s\n", yytext); prev_token = incre_; return incre_;}
{decre}			{printf("%s\n", yytext); prev_token = decre_; return decre_;}
{equality}		{printf("%s\n", yytext); prev_token = equality_; return equality_;}
{lt}            {printf("%s\n", yytext); prev_token = '<'; return '<';}
{gt}            {printf("%s\n", yytext); prev_token = '>'; return '>';}
{eq}            {printf("%s\n", yytext); prev_token = '='; return '=';}
{not}           {printf("%s\n", yytext); prev_token = '!'; return '!';}
{not_eq}        {printf("%s\n", yytext); prev_token = not_eq_; return not_eq_;}
{lteq}          {printf("%s\n", yytext); prev_token = lteq_; return lteq_;}
{gteq}			{printf("%s\n", yytext); prev_token = gteq_; return gteq_;}
{decla}         {printf("%s\n", yytext); prev_token = decla_; return decla_;}
{etc}           {printf("%s\n", yytext); prev_token = etc_; return etc_;}
{lrbrac}		{printf("%s\n", yytext); prev_token = '('; return '(';}
{rrbrac}		{printf("%s\n", yytext); prev_token = ')'; return ')';}
{lsbrac}		{printf("%s\n", yytext); prev_token = '['; return '[';}
{rsbrac}		{printf("%s\n", yytext); prev_token = ']'; return ']';}
{lcbrac}		{printf("%s\n", yytext); prev_token = '{'; return '{';}
{rcbrac}		{printf("%s\n", yytext); prev_token = '}'; return '}';}
{comma}			{printf("%s\n", yytext); prev_token = ','; return ',';}
{dot}			{printf("%s\n", yytext); prev_token = '.'; return '.';}
{colon} 		{printf("%s\n", yytext); prev_token = ':'; return ':';}
{vb}			{printf("%s\n", yytext); prev_token = '|'; return '|';}

{rune_lit}		{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = rune_lit_;
					return rune_lit_;
				}

{int_lit}		{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = int_lit;
					return int_lit;
				}

{float_lit}			{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = float_lit;
					return float_lit;
				}
{string_lit}	{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = string_lit_;
					return string_lit_;
				}

{semi_colon}	{printf("%s\n", yytext); prev_token = ';'; return ';';}

{ID}			{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					prev_token = id_;
					return id_;
				}

" "|"\t"		char_num++;
"\n"			{
					line_num += 1;
					temp = prev_token;
					prev_token = 0;
					switch(temp){
						case id_: return ';';
						case int_lit_: return ';';
						case float_lit_: return ';';
						case string_lit_: return ';';
						case rune_lit_: return ';';
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

<INITIAL><<EOF>>        {
							BEGIN(REALLYEND);
							switch(prev_token){
								case id_: return ';';
								case int_lit_: return ';';
								case float_lit_: return ';';
								case string_lit_: return ';';
								case rune_lit_: return ';';
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
