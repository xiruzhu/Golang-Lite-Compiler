#!/bin/bash
if [ "$#" -ge 3 ]; then
	L=$1
	Y=$2
	S=$3
else
	echo "Enter L File Y File and Source file"
	read L Y S
fi

flex $L && bison $Y && clang lex.yy.c -o goCompiler -lfl

if [ "$#" -eq 4 ]; then
	cat $S | ./goCompiler $4
else
	cat $S | ./goCompiler
fi

