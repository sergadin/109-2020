CC=gcc 
CFLAGS=-g

all: do-test clean

rank.o: rank.c rank.h
#	gcc -c rank.c 

testM.o: testM.c rank.h
#	gcc -c testM.c 

a.out: testM.o rank.o
	gcc testM.o rank.o -lm

do-test: a.out
	./a.out 

clean: testM.o rank.o
	rm testM.o rank.o 
