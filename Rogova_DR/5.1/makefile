CC=gcc
CFLAGS=-g

all: do-test clean

test5.o: test5.cpp interpol.h
#	gcc -c test5.cpp

a.out: test5.o interpol.h
	gcc test5.o interpol.h

do-test: a.out
	./a.out

clean: test5.o interpol.h
	rm test5.o interpol.h
