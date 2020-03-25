CC=gcc
CFLAGS=-g

all: do-test clean

inte.o: root.c root.h
#	gcc -c root.c

test.o: test1.o root.h
#	gcc -c root.c

a.out: test1.o root.o
	gcc test1.o root.o

do-test: a.out
	./a.out

clean: test1.o root.o
	rm test1.o root.o
