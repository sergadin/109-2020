CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: rank.c rank.h
#	gcc -c rank.c

sum_test.o: test.o rank.h
#	gcc -c test.c

a.out: test.o rank.o
	gcc test.o rank.o -lm

do-test: a.out
	./a.out

clean: test.o rank.o
	rm test.o rank.o