CC=gcc 
CFLAGS=-g

all: do-test clean

obr.o: obr.c obr.h
#	gcc -c obr.c 

testm.o: testm.c obr.h
#	gcc -c testM.c 

a.out: testM.o rank.o
	gcc testM.o rank.o -lm

do-test: a.out
	./a.out 

clean: testM.o mini.o
	rm testM.o rank.o 
