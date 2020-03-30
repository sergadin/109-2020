CC=gcc
CFLAGS=-g

all: do-test clean

decision.1.1.o: decision.1.1.c decision.1.1.h
#	gcc -c decision.1.1.c

test.o: test.o decision.1.1.h
#	gcc -c decision.1.1.c

a.out: test.o decision.1.1.o
	gcc test.o decision.1.1.o

do-test: a.out
	./a.out

clean: test.o decision.1.1.o
	rm test.o decision.1.1.o
