CC=gcc
CFLAGS=-g

all: do-test clean

sum.o sum.c sum.h

test.o: test.o sum.h

a.out: test.o sum.o
	gcc test.o sum.o

do-test: a.out
	./a.out

clean: test.o sum.o
	rm sum.o sum.o