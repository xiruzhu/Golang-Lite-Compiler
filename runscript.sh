#/bin/sh

printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
flex go.l && bison go.y && clang lex.yy.c -o goCompiler -lfl -lm

for file in $1/*.go;
do
	printf "On file $file\n\n"
	cat $file | ./goCompiler
	printf "\n\nEnd file $file\n\n"
	printf "________________________________________________________________\n\n"
done