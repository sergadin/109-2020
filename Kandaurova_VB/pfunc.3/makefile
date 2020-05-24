CC=gcc 
CFLAGS=-g

all: do-test clean

pfunc.o: pfunc.c pfunc.h
#	gcc -c det.c 

test.o: test.c pfunc.h
#	gcc -c test.c 

a.out: test.o pfunc.o
	gcc test.o pfunc.o -lm

do-test: a.out
	./a.out 

clean: test.o pfunc.o
	rm test.o pfunc.o 
