CC=gcc
CFLAGS=-g

all: do-test clean

minimum.o: minimum.c minimum.h
#	gcc -c minimum.c

test_minimum.o: test_minimum.c minimum.h
#	gcc -c test_simpson.c

a.out: test_minimum.o minimum.o
	gcc test_simpson.o minimum.o -lm

do-test: a.out
	./a.out

clean: test_minimum.o minimum.o a.out
	rm test_minimum.o minimum.o a.out
