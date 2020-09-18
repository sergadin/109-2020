CC=gcc
CFLAGS= -g

all: do-test clean

sum.o: process.c process.h
# gcc -c process.c

sum_test.o: test.o process.h
# gcc -c test.c

a.out: test.o process.o
gcc test.o process.o -lm

do-test: a.out
./a.out

clean: test.o process.o
rm test.o process.o