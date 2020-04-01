CC=gcc
CFLAGS=-g

all: do-test clean

svertka.o: svertka.c svertka.h
#	gcc -c svertka.c

test_svertka.o: test_svertka.c svertka.h
#	gcc -c test_svertka.c

a.out: test_svertka.o svertka.o
	gcc test_svertka.o svertka.o

do-test: a.out
	./a.out

clean: test_svertka.o svertka.o
	rm test_svertka.o svertka.o a.out leak.out
	
