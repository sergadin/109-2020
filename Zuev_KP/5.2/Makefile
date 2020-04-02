CC=gcc 
CFLAGS=-g

all: do-test clean

test.o: test52.o kuslin.h
#	g++ -c test52.cpp 

a.out: test52.o kuslin.o
	gcc test52.o kuslin.o -lm

do-test: a.out
	./a.out 

clean: test52.o kuslin.o
	rm test52.o kuslin.o 
