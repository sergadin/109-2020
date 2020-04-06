CC=gcc
CFLAGS=-g

all: do-test clean

test.o: test.o pribl.h
#	g++ -c test.cpp

a.out: test.o
	g++ test.o

do-test: a.out
	./a.out

clean: test.o pribl.h
	rm test.o
