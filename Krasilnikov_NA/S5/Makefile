CC=gcc
CFLAGS=-g

all: do-test clean

mystring.o: ../libs/mystring/mystring.h ../libs/mystring/mystring.c
	gcc -c -g ../libs/mystring/mystring.c

words.o: ../libs/mystring/mystring.h words.h words.c
	gcc -c -g words.c

words_test.o: words.h words_test.c
	gcc -c -g words_test.c

a.out: mystring.o words.o words_test.o
	gcc -o  a.out mystring.o words.o words_test.o

do-test: a.out
	valgrind ./a.out -g

clean: mystring.o words.o words_test.o a.out
	rm mystring.o words.o words_test.o a.out
