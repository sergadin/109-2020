CC=gcc
CFLAGS=-g

all: do-test clean

interpol.o: interpol.c interpol.h
#	gcc -c interpol.c

test5.o: test5.o interpol.h
#	gcc -c interpol.c

a.out: test5.o interpol.o
	gcc test5.o interpol.o

do-test: a.out
	./a.out

clean: test5.o interpol.o
	rm test5.o interpol.o
