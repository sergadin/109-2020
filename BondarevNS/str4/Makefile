CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: find.c find.h
#	gcc -c find.c

sum_test.o: test.o find.h
#	gcc -c test.c

a.out: test.o find.o
	gcc test.o find.o -lm

do-test: a.out
	./a.out

clean: test.o find.o
	rm test.o find.o
