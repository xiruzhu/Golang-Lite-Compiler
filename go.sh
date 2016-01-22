#!/bin/bash
if [ "$#" -eq 2 ]; then
	L=$1
	S=$2
else
	echo "Enter L File"
	read L S
fi

flex $L
gcc -std=c99 lex.yy.c -lfl -o run

cat $S | ./run
