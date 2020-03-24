CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test.o func.h
#	gcc -c test.c

a.out: test.o func.o
	gcc test.o func.o

do-test: a.out
	./a.out

clean: test.o func.o
	rm test.o func.o
