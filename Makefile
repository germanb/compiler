obj = lex.yy.o ts.o parser.o error.o sistejec.o
CC = gcc
CFLAGS = -g

ucc: $(obj)
	gcc -o $@ $(obj) -lm

parser.o: parser.c codigos.h var_globales.h

lex.yy.o: lex.yy.c codigos.h var_globales.h

sistejec.0: sistejec.c soporte_ejecucion.h

ts.o: ts.c ts.h

error.o: error.c error.h var_globales.h

clean:
	$(RM) $(obj)    
