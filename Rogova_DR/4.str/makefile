CC=gcc 
CFLAGS=-g

all: do-test clean

findstr.o: findstr.c findstr.h
#	gcc -c findstr.c 

teststr4.o: teststr4.c findstr.h
#	gcc -c teststr4.c 

a.out: teststr4.o findstr.o
	gcc teststr4.o findstr.o -lm

do-test: a.out
	./a.out 

clean: teststr4.o findstr.o
	rm teststr4.o findstr.o 
