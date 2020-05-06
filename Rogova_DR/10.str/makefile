CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: findstr.c findstr.h
#	gcc -c findstr.c

sum_test.o: teststr4.o findstr.h
#	gcc -c test10.c

a.out: teststr4.o findstr.o
	gcc teststr4.o findstr.o -lm

do-test: a.out
	./a.out

clean: teststr4.o findstr.o
	rm teststr4.o findstr.o
