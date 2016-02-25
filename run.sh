#!/bin/bash
if [ "$#" -eq 3 ]; then
	L=$1
	Y=$2
	S=$3
else
	echo "Enter L File Y File and Source file"
	read L Y S
fi

bison --yacc --defines --verbose $Y
flex $L
gcc -std=c99 lex.yy.c -lfl -o run
cat $S | ./run

