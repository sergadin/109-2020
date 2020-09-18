CC=gcc
CFLAGS=-g

all: do-test clean

process.o: process.h process.c
	gcc -c -g process.c

test.o: process.h process.c
	gcc -c -g test.c 

a.out: process.o test.o
	gcc -o a.out process.o test.o

do-test: a.out
	valgrind ./a.out

clean: process.o test.o
	rm process.o test.o