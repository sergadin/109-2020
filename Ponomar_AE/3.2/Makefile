CC=gcc 
CFLAGS=-g

all: do-test clean

minimum.o: minimum.c minimum.h
#	gcc -c minimum.c 

test.o: test.o minimum.h
#	gcc -c test.c 

a.out: test.o minimum.o
	gcc test.o minimum.o -lm

do-test: a.out
	./a.out 

clean: test.o minimum.o
	rm test.o minimum.o 
