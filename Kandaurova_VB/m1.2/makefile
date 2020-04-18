CC=gcc 
CFLAGS=-g

all: do-test clean

det.o: det.c det.h
#	gcc -c det.c 

test.o: test.c det.h
#	gcc -c test.c 

a.out: test.o det.o
	gcc test.o det.o -lm

do-test: a.out
	./a.out 

clean: test.o det.o
	rm test.o det.o 
