%{
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"

int line_num = 1;
int char_num = 1;

char* tokens[3000];
size_t numToken = 0;
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

escaped_char    '\'("a"|"b"|"f"|"n"|"r"|"t"|"v"|`\`|"'"|`"`)
string_lit		{raw_string_lit}|{interpreted_string_lit}
raw_string_lit	\'(" "|'!'|[#-_]|[a-~]|escaped_char)*\'
interpreted_string_lit	\"(" "|'!'|[#-_]|[a-~]|escaped_char)*\"
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
{break}			{printf("%s\n", yytext); return break_;}
{case}			{printf("%s\n", yytext); return case_;}
{chan}			{printf("%s\n", yytext); return chan_;}
{const}         {printf("%s\n", yytext); return const_;}
{continue}		{printf("%s\n", yytext); return continue_;}
{default}		{printf("%s\n", yytext); return default_;}
{defer}			{printf("%s\n", yytext); return defer_;}
{else}			{printf("%s\n", yytext); return else_;}
{fallthrough}	{printf("%s\n", yytext); return fallthrough_;}
{for}           {printf("%s\n", yytext); return for_;}
{func}          {printf("%s\n", yytext); return func_;}
{go}            {printf("%s\n", yytext); return go_;}
{goto}          {printf("%s\n", yytext); return goto_;}
{if}            {printf("%s\n", yytext); return if_;}
{import}        {printf("%s\n", yytext); return import_;}
{interface}     {printf("%s\n", yytext); return interface_;}
{map}           {printf("%s\n", yytext); return map_;}
{package}       {printf("%s\n", yytext); return package_;}
{range}			{printf("%s\n", yytext); return range_;}
{return} 		{printf("%s\n", yytext); return return_;}
{select} 		{printf("%s\n", yytext); return select_;}
{struct}		{printf("%s\n", yytext); return struct_;}
{switch}		{printf("%s\n", yytext); return switch_;}
{type}			{printf("%s\n", yytext); return type_;}
{var}			{printf("%s\n", yytext); return var_;}
{bool}          {printf("%s\n", yytext); return bool_;}
{rune}          {printf("%s\n", yytext); return rune_;}
{string}        {printf("%s\n", yytext); return string_;}
{print}         {printf("%s\n", yytext); return print_;}
{println}       {printf("%s\n", yytext); return println_;}
{append}		{printf("%s\n", yytext); return append_;}
{add}			{printf("%s\n", yytext); return '+';}
{minus}			{printf("%s\n", yytext); return '-';}
{mult}			{printf("%s\n", yytext); return '*';}
{div}			{printf("%s\n", yytext); return '/';}
{mod}			{printf("%s\n", yytext); return '%';}
{amp}			{printf("%s\n", yytext); return '&';}
{caret}			{printf("%s\n", yytext); return '^';}
{ls}			{printf("%s\n", yytext); return '<<';}
{rs}			{printf("%s\n", yytext); return '>>;}
{unknown} 		{printf("%s\n", yytext); return '&^';}
{add_eq}		{printf("%s\n", yytext); return '+=';}
{minus_eq}		{printf("%s\n", yytext); return '-=';}
{mult_eq}		{printf("%s\n", yytext); return '*=';}
{div_eq}		{printf("%s\n", yytext); return '/=';}
{mod_eq}		{printf("%s\n", yytext); return '%=';}
{amp_eq}		{printf("%s\n", yytext); return '&=';}
{vb_eq}			{printf("%s\n", yytext); return '/=';}
{caret_eq}		{printf("%s\n", yytext); return '%=';}
{ls_eq}			{printf("%s\n", yytext); return '<<=';}
{rs_eq}			{printf("%s\n", yytext); return '>>=';}
{unknown_eq}	{printf("%s\n", yytext); return '&^=';}
{and}           {printf("%s\n", yytext); return '&&';}
{or}			{printf("%s\n", yytext); return '||';}
{arrow} 		{printf("%s\n", yytext); return '<-';}
{incre}         {printf("%s\n", yytext); return '++';}
{decre}			{printf("%s\n", yytext); return '--';}
{equality}		{printf("%s\n", yytext); return '==';}
{lt}            {printf("%s\n", yytext); return '<';}
{gt}            {printf("%s\n", yytext); return '>';}
{eq}            {printf("%s\n", yytext); return '=';}
{not}           {printf("%s\n", yytext); return '!';}
{not_eq}        {printf("%s\n", yytext); return '!=';}
{lteq}          {printf("%s\n", yytext); return '<=';}
{gteq}			{printf("%s\n", yytext); return '>=';}
{decla}         {printf("%s\n", yytext); return ':=';}
{etc}           {printf("%s\n", yytext); return '...';}
{lrbrac}		{printf("%s\n", yytext); return '(';}
{rrbrac}		{printf("%s\n", yytext); return ')';}
{lsbrac}		{printf("%s\n", yytext); return '[';}
{rsbrac}		{printf("%s\n", yytext); return ']';}
{lcbrac}		{printf("%s\n", yytext); return '{';}
{rcbrac}		{printf("%s\n", yytext); return '}';}
{comma}			{printf("%s\n", yytext); return ',';}
{dot}			{printf("%s\n", yytext); return '.';}
{colon} 		{printf("%s\n", yytext); return ':';}
{vb}			{printf("%s\n", yytext); return '|';}

{int_lit}		{
					char ** temp;
					printf("%s\n", yytext);
					yylval.int_val = strtol(yytext, temp, 10);
					if(temp != NULL){
						printf("Integer parse error %s\n", yytext);
						return error_;
					}
					return int_lit_;
				}

{float_lit}			{
					char ** temp;
					printf("%s\n", yytext);
					yylval.float_val = strtof(yytext, temp);
					if(temp != NULL){
						printf("Integer parse error %s\n", yytext);
						return error_;
					}
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
					return string_lit_;
				}

{semi_colon}	{printf("%s\n", yytext); return ';';}

{ID}			{
					char * val = (char *)malloc(strlen(yytext) + 1);
					if(val == NULL){
						printf("Mem Alloc Failed\n");
						exit(1);
					}
					printf("%s\n", yytext);
					strcpy(val, yytext);
					yylval.str_val = val;
					return ID_;
				}

" "|"\t"		char_num++;
""
"\n"			{line_num++; return new_line_;}
			//ok
%%

