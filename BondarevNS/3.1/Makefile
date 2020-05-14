CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: sum.c sum.h

test.o: test.c sum.h

a.out: test.o sum.o
	gcc test.o sum.o -lm

do-test: a.out
	./a.out

clean: test.o sum.o ./a.out
	rm test.o sum.o ./a.out