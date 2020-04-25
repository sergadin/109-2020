CC=gcc
CFLAGS=-g

all: do-test clean

Words_Length.o: Words_Length.c Words_Length.h

test_Words_Length.o: test_Words_Length.c Words_Length.h

a.out: test_Words_Length.o Words_Length.o
	gcc test_Words_Length.o Words_Length.o -lm

do-test: a.out
	valgrind ./a.out

clean: test_Words_Length.o Words_Length.o
	rm test_Words_Length.o Words_Length.o a.out
