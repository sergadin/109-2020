CC=gcc
CFLAGS=-g

all: do-test clean

inte.o: decision.c decision.h
#	gcc -c decision.c

test.o: test_file_1.1.o decision.h
#	gcc -c decision.c

a.out: test_file_1.1.o decision.o
	gcc test_file_1.1.o decision.o

do-test: a.out
	./a.out

clean: test_file_1.1.o decision.o
	rm test_file_1.1.o decision.o
