CC=gcc 
CFLAGS=-g

all: do-test clean

file.o: file.c file.h
#	gcc -c str.c 

test.o: test.c file.h
#	gcc -c test.c 

a.out: test.o file.o
	gcc test.o file.o -lm

do-test: a.out
	./a.out input.txt sy i o pop po
clean: test.o file.o
	rm test.o file.o 
