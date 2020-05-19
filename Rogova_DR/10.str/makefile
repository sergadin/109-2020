CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: findstr1.c findstr1.h
#	gcc -c findstr1.c

sum_test.o: teststr4.o findstr1.h
#	gcc -c test10.c

a.out: teststr4.o findstr1.o
	gcc teststr4.o findstr1.o -lm

do-test: a.out
	./a.out

clean: teststr4.o findstr1.o
	rm teststr4.o findstr1.o
