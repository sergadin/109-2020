CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: sum.c sum.h
	gcc -c sum.c -o sum.o

test_sum.o: test_sum.c sum.h
	gcc -c test_sum.c

a.out: test_sum.o sum.o
	gcc test_sum.o sum.o

do-test: a.out
	./a.out

clean: test_sum.o sum.o
	rm test_sum.o sum.o a.out leak.out
	
