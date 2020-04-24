CC=gcc
CFLAGS=-g

all: do-test clean

Det.o: Det.c Det.h

test_Det.o: test_Det.c Det.h

a.out: test_Det.o Det.o
	gcc test_Det.o Det.o -lm

do-test: a.out
	valgrind ./a.out

clean: test_Det.o Det.o
	rm test_Det.o Det.o a.out
