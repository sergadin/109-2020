CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test11.o func.h
#	gcc -c test11.c

a.out: test11.o func.o
	gcc test11.o func.o

do-test: a.out
	./a.out

clean: test11.o func.o
	rm test11.o func.o
