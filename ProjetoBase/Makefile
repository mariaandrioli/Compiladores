$DEPURA=1

compilador: lex.yy.c y.tab.c compilador.o compilador.h functions.o functions.h
	gcc lex.yy.c compilador.tab.c compilador.o functions.o -o compilador -ll -ly -lc

lex.yy.c: compilador.l compilador.h
	flex compilador.l

y.tab.c: compilador.y compilador.h
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

functions.o : functions.h functions.c compilador.h
	gcc -c functions.c -o functions.o

clean : 
	rm -f compilador.tab.* lex.yy.c  *.o compilador
