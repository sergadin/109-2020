CC=gcc
CFLAGS=-g

all: do-test clean

Newton.o: Newton.c Newton.h
#	gcc -c Newton.c

test_Newton.o: test_Newton.c Newton.h
#	gcc -c test_Newton.c

a.out: test_Newton.o Newton.o
	gcc test_Newton.o Newton.o -lm

do-test: a.out
	./a.out

clean: test_Newton.o Newton.o
	rm test_Newton.o Newton.o a.out
