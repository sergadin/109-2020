CC=gcc
CFLAGS=-g

all: do-test clean

integral.o: integral.c integral.h
#	gcc -c integral.c

test.o: test.o integral.h
#	gcc -c test.c

a.out: test.o integral.o
	gcc test.o integral.o -lm

do-test: a.out
	./a.out

clean: test.o integral.o
	rm test.o integral.o
