CC=gcc
CFLAGS=-g

all: do-test clean

test5.o: test5.cpp interpol.h
#	g++ -c test5.cpp

do-test: a.out
	./a.out

clean: test5.o interpol.h
	rm test5.o
