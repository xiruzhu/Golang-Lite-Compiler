#!/bin/bash
if [ "$#" -eq 1 ]; then
	L=$1
else
	echo "Enter L File and Source file"
	read L
fi

flex $L
gcc -std=c99 lex.yy.c -lfl -o run