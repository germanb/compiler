obj = lex.yy.o ts.o parser.o error.o
CC = gcc
CFLAGS = -g

ucc: $(obj)
	gcc -o $@ $(obj) -lm

parser.o: parser.c codigos.h var_globales.h

lex.yy.o: lex.yy.c codigos.h var_globales.h

ts.o: ts.c ts.h

error.o: error.c error.h var_globales.h

clean:
	$(RM) $(obj)    
