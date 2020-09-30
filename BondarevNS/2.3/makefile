CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: simp.c simp.h

test.o: simp.c simp.h

a.out: test.o simp.o
	gcc test.o simp.o -lm

do-test: a.out
	./a.out

clean: test.o simp.o ./a.out
	rm test.o simp.o ./a.out