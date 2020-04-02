CC=gcc
CFLAGS=-g

all: do-test clean

test.o: test52.cpp  kuslin.h
#	g++ -c test52.c

do-test: a.out
	./a.out

clean: test52.o kuslin.h
	rm test52.o 
