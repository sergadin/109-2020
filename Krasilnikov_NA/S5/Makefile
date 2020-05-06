CC=gcc
CFLAGS=-g

all: do-test clean

mystring.o: ../libs/mystring/mystring.h ../libs/mystring/mystring.c
	gcc -c -g ../libs/mystring/mystring.c

format.o: ../libs/mystring/mystring.h format.h format.c
	gcc -c -g format.c

format_test.o: format.h format_test.c
	gcc -c -g format_test.c

a.out: mystring.o format.o format_test.o
	gcc -o  a.out mystring.o format.o format_test.o

do-test: a.out
	valgrind ./a.out -g 

clean: mystring.o format.o format_test.o a.out
	rm mystring.o format.o format_test.o a.out
