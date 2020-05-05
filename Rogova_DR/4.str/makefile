CC=gcc
CFLAGS=-g

all: do-test clean

inte.o: findstr.c findstr.h
#	gcc -c findstr.c

test.o: teststr4.o findstr.h
#	gcc -c findstr.c

a.out: teststr4.o findstr.o
	gcc teststr4.o findstr.o

do-test: a.out
	./a.out

