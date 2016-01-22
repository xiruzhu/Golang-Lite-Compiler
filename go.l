%{
#include <stdio.h>
#include <stdlib.h>
int num_char = 0, num_line = 0;
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

%%
"\n"			num_line++;
"//".*		{
			printf("Eating ...%s\n", yytext);
			num_char += strlen(yytext);
			}

\/\*([^\*]|\*+^\/)*\*\/ {
			printf("Eating ...%s\n", yytext);
			for(int i = 0; i < strlen(yytext); i++)
				if(yytext[i] == '\n')
					num_line++;
			}
{break}			{printf("%s\n", yytext);}
{case}			{printf("%s\n", yytext);}
{chan}			{printf("%s\n", yytext);}
{const}         {printf("%s\n", yytext);}
{continue}		{printf("%s\n", yytext);}
{default}		{printf("%s\n", yytext);}
{defer}			{printf("%s\n", yytext);}
{else}			{printf("%s\n", yytext);}
{fallthrough}	{printf("%s\n", yytext);}
{for}           {printf("%s\n", yytext);}
{func}          {printf("%s\n", yytext);}
{go}            {printf("%s\n", yytext);}
{goto}          {printf("%s\n", yytext);}
{if}            {printf("%s\n", yytext);}
{import}        {printf("%s\n", yytext);}
{interface}     {printf("%s\n", yytext);}
{map}           {printf("%s\n", yytext);}
{package}       {printf("%s\n", yytext);}
{range}			{printf("%s\n", yytext);}
{return} 		{printf("%s\n", yytext);}
{select} 		{printf("%s\n", yytext);}
{struct}		{printf("%s\n", yytext);}
{switch}		{printf("%s\n", yytext);}
{type}			{printf("%s\n", yytext);}
{var}			{printf("%s\n", yytext);}
{bool}          {printf("%s\n", yytext);}
{rune}          {printf("%s\n", yytext);}
{string}        {printf("%s\n", yytext);}
{print}         {printf("%s\n", yytext);}
{println}       {printf("%s\n", yytext);}
{append}		{printf("%s\n", yytext);}
{minus}			{printf("%s\n", yytext);}
{mult}			{printf("%s\n", yytext);}
{div}			{printf("%s\n", yytext);}
{mod}			{printf("%s\n", yytext);}
{amp}			{printf("%s\n", yytext);}
{caret}			{printf("%s\n", yytext);}
{ls}			{printf("%s\n", yytext);}
{rs}			{printf("%s\n", yytext);}
{unknown} 		{printf("%s\n", yytext);}
{add_eq}		{printf("%s\n", yytext);}
{minus_eq}		{printf("%s\n", yytext);}
{mult_eq}		{printf("%s\n", yytext);}
{div_eq}		{printf("%s\n", yytext);}
{mod_eq}		{printf("%s\n", yytext);}
{amp_eq}		{printf("%s\n", yytext);}
{vb_eq}			{printf("%s\n", yytext);}
{caret_eq}		{printf("%s\n", yytext);}
{ls_eq}			{printf("%s\n", yytext);}
{rs_eq}			{printf("%s\n", yytext);}
{unknown_eq}	{printf("%s\n", yytext);}
{and}           {printf("%s\n", yytext);}
{or}			{printf("%s\n", yytext);}
{arrow} 		{printf("%s\n", yytext);}
{incre}         {printf("%s\n", yytext);}
{decre}			{printf("%s\n", yytext);}
{equality}		{printf("%s\n", yytext);}
{lt}            {printf("%s\n", yytext);}
{gt}            {printf("%s\n", yytext);}
{eq}            {printf("%s\n", yytext);}
{not}           {printf("%s\n", yytext);}
{not_eq}        {printf("%s\n", yytext);}
{lteq}          {printf("%s\n", yytext);}
{gteq}			{printf("%s\n", yytext);}
{decla}         {printf("%s\n", yytext);}
{etc}           {printf("%s\n", yytext);}
{lrbrac}		{printf("%s\n", yytext);}
{rrbrac}		{printf("%s\n", yytext);}
{lsbrac}		{printf("%s\n", yytext);}
{rsbrac}		{printf("%s\n", yytext);}
{lcbrac}		{printf("%s\n", yytext);}
{rcbrac}		{printf("%s\n", yytext);}
{comma}			{printf("%s\n", yytext);}
{dot}			{printf("%s\n", yytext);}
{colon} 		{printf("%s\n", yytext);}
{vb}			{printf("%s\n", yytext);}
{int_lit}		{printf("%s\n", yytext);}
{float}			{printf("%s\n", yytext);}
{string_lit}	{printf("%s\n", yytext);}
{semi_colon}	{printf("%s\n", yytext);}
{ID}			{printf("%s\n", yytext);}
" "|"\t"		num_char++;

%%

int main(){
	printf("Init Flex\n");
	yylex();
	return 0;
}

