CC=gcc
CFLAGS=-g

all: do-test clean

Det.o: Det.c Det.h
#	gcc -c Det.c

test_Det.o: test_Det.c Det.h
#	gcc -c test_Taylor.c

a.out: test_Det.o Det.o
	gcc test_Det.o Det.o -lm

do-test: a.out
	./a.out

clean: test_Det.o Det.o
	rm test_Det.o Det.o a.out
