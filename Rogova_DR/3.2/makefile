CC=gcc 
CFLAGS=-g

all: do-test clean

mini.o: mini.c mini.h
#	gcc -c mini.c 

test3.o: test3.o mini.h
#	gcc -c test3.c 

a.out: test3.o mini.o
	gcc test3.o mini.o -lm

do-test: a.out
	./a.out 

clean: test3.o mini.o
	rm test3.o mini.o 
