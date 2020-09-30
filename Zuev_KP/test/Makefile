CC=gcc
CFLAGS=-g

all: do-test clean

test.o: test.o kuslin.h
#	g++ -c test.cpp

a.out: test.o
	g++ test.o

do-test: a.out
	./a.out

clean: test.o kuslin.h
	rm test.o 
