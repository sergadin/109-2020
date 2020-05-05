CC=gcc 
CFLAGS=-g

all: do-test clean

back.o: back.c back.h
#	gcc -c back.c 

test.o: test.c back.h
#	gcc -c test.c 

a.out: test.o back.o
	gcc test.o back.o -lm

do-test: a.out
	./a.out 

clean: test.o back.o
	rm test.o back.o 
