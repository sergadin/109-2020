CC=gcc 
CFLAGS=-g

all: do-test clean

log4.o: log4.c log4.h
#	gcc -c log4.c 

test4.o: test4.o log4.h
#	gcc -c test4.c 

a.out: test4.o log4.o
	gcc test4.o log4.o -lm

do-test: a.out
	./a.out 

clean: test4.o log4.o
	rm test4.o log4.o 
