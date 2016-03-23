FLEX = flex
BISON = bison
CC = clang -g

FLAG = -DPPTYPE -DDUMPSYMTAB
SRC_PATH = "./src/"

goLite : 
	$(FLEX) ./src/go.l
	$(BISON) ./src/go.y
	$(CC) -I$(SRC_PATH) $(FLAG) lex.yy.c -o goLite -lfl -lm

clean :
	rm go.tab.c lex.yy.c goLite
