CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: cos.c cos.h

test.o: test.c cos.h

a.out: test.o cos.o
	gcc test.o cos.o -lm

do-test: a.out
	./a.out

clean: test.o cos.o ./a.out
	rm test.o cos.o ./a.out