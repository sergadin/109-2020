CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test23.o func.h
#	gcc -c test23.c

a.out: test23.o func.o
	gcc test23.o func.o

do-test: a.out
	./a.out

clean: test23.o func.o
	rm test23.o func.o
