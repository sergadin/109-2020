CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: root.c root.h

test.o: root.c root.h

a.out: test.o root.o
	gcc test.o root.o -lm

do-test: a.out
	./a.out

clean: test.o root.o ./a.out
	rm test.o root.o ./a.out