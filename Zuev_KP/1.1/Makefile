CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test4.o func.h
#	gcc -c test4.c

a.out: test4.o func.o
	gcc test4.o func.o

do-test: a.out
	./a.out

clean: test4.o func.o
	rm test4.o func.o
