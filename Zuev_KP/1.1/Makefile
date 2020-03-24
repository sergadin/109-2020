CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test1.o func.h
#	gcc -c test1.c

a.out: test1.o func.o
	gcc test1.o func.o

do-test: a.out
	./a.out

clean: test1.o func.o
	rm test1.o func.o
