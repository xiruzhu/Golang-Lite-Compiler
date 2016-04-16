CC   = clang
FLAG = -std=c99
LIB  = -ll -lm

LEX  = flex
YACC = bison

GoLite : 
	flex go.l
	bison go.y
	$(CC) $(FLAG) lex.yy.c -o GoLite $(LIB)

clean:
	rm go.tab.c
	rm lex.yy.c
	rm GoLite