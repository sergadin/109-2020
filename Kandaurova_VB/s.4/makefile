CC=gcc 
CFLAGS=-g

all: do-test clean

back.o: str.c str.h
#	gcc -c str.c 

test.o: test.c str.h
#	gcc -c test.c 

a.out: test.o str.o
	gcc test.o str.o -lm

do-test: a.out
	./a.out 

clean: test.o str.o
	rm test.o str.o 
