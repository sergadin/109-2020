all: do-test clean

func.o: func.c func.h
	gcc -c func.c

stroki.o: stroki.c func.h
	gcc -c stroki.c

a.out: stroki.o func.o
	gcc stroki.o func.o

do-test: a.out
	valgrind -v ./a.out

clean: stroki.o func.o
	rm stroki.o func.o
