CC=gcc
CFLAGS=-g

all: do-test clean

33.o: 33.h 33.c
	gcc -c -g 33.c

33_test.0: 33.h 33.c
	gcc -c -g 33_test.c

a.out: 33.o 33_test.o
	gcc -o a.out 33.o 33_test.o

do-test: a.out
	valgrind ./a.out

clean: 33.o 33_test.0 a.out
	rm 33.o 33_test.o a.out
