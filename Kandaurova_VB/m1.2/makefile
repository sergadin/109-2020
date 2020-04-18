CC=gcc 
CFLAGS=-g

all: do-test clean

det.o: det.c det.h
#	gcc -c obr.c 

test.o: test.c det.h
#	gcc -c testm.c 

a.out: test.o det.o
	gcc test.o det.o -lm

do-test: a.out
	./a.out 

clean: test.o det.o
	rm test.o det.o 
