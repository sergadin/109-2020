CC=gcc
CFLAGS=-g

all: do-test clean

Taylor.o: Taylor.c Taylor.h
#	gcc -c Taylor.c

test_Taylor.o: test_Taylor.c Taylor.h
#	gcc -c test_Taylor.c

a.out: test_Taylor.o Taylor.o
	gcc test_Taylor.o Taylor.o -lm

do-test: a.out
	./a.out

clean: test_Taylor.o Taylor.o
	rm test_Taylor.o Taylor.o a.out
