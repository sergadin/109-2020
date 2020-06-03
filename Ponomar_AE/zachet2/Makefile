all: do-test

zachet.o: zachet.c zachet.h
	gcc -c zachet.c

test.o: test.c zachet.h
	gcc -c test.c

a.out: test.o zachet.o
	gcc test.o zachet.o

do-test: a.out
	./a.out
