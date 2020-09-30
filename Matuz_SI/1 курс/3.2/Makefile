all: do-test

min.o: min.c min.h
	gcc -c min.c

test.o: test.c min.h
	gcc -c test.c

a.out: test.o min.o
	gcc test.o min.o -lm

do-test: a.out
	./a.out
	
