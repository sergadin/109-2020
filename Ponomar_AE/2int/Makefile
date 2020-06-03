CC=gcc 
CFLAGS=-g

all: do-test clean

2int.o: 2int.c 2int.h
#	gcc -c 2int.c 

main.o: main.o 2int.h
#	gcc -c main.c 

a.out: main.o 2int.o
	gcc main.o 2int.o -lm

do-test: a.out
	./a.out 

clean: main.o 2int.o
	rm main.o 2int.o 
