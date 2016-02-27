BISON = bison
FLEX = flex
CC = clang

goLite	:
	$(FLEX) go.l
	$(BISON) go.y
	$(CC) lex.yy.c -o goLite -ll
	
clean	:	
	rm lex.yy.c go.tab.c goLite