CC=gcc
CFLAGS=-g

all: do-test clean

simpson.o: simpson.c simpson.h
#	gcc -c simpson.c

test_simpson.o: test_simpson.c simpson.h
#	gcc -c test_simpson.c

a.out: test_simpson.o simpson.o
	gcc test_simpson.o simpson.o

do-test: a.out
	./a.out

clean: test_simpson.o simpson.o
	rm test_simpson.o simpson.o a.out leak.out
