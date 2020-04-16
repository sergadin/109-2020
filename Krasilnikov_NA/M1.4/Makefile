CC=gcc
CFLAGS=-g

all: do-test clean

Sole.o: Sole.c Sole.h
#	gcc -c Sole.c

test_Sole.o: test_Sole.c Sole.h
#	gcc -c test_Sole.c

a.out: test_Sole.o Sole.o
	gcc test_Sole.o Sole.o -lm

do-test: a.out
	./a.out

clean: test_Sole.o Sole.o
	rm test_Sole.o Sole.o a.out
