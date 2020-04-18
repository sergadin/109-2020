CC=gcc 
CFLAGS=-g

all: do-test clean

obr.o: obr.c obr.h
#	gcc -c obr.c 

testm.o: testm.c obr.h
#	gcc -c testm.c 

a.out: testm.o obr.o
	gcc testm.o obr.o -lm

do-test: a.out
	./a.out 

clean: testm.o obr.o
	rm testm.o obr.o 
