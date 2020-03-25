CC=gcc 
CFLAGS=-g

all: do-test clean

func.o: func.c func.h
#	gcc -c func.c 

test.o: test23.o func.h
#	gcc -c test23.c 

a.out: test23.o func.o
	gcc test23.o func.o -lm

do-test: a.out
	./a.out 

clean: test23.o func.o
	rm test23.o func.o 
