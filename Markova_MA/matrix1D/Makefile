CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: f.c f.h
#	gcc -c f.c

sum_test.o: test.o f.h
#	gcc -c test10.c

a.out: test.o f.o
	gcc test.o f.o -lm

do-test: a.out
	./a.out

clean: test.o f.o
	rm test.o f.o