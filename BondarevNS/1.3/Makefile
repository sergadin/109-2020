CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: root.c root.h

test.o: root.c root.h

a.out: root.o root.o
	gcc root.o root.o -lm

do-test: a.out
	./a.out

clean: root.o root.o ./a.out
	rm test.o root.o ./a.out