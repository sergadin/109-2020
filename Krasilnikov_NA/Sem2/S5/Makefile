CC=gcc
CFLAGS=-g

all: do-test clean

mystring.o: ../libs/mystring/mystring.h ../libs/mystring/mystring.c
	gcc -c -g ../libs/mystring/mystring.c

strings_words_symbols.o: ../libs/mystring/mystring.h strings_words_symbols.h strings_words_symbols.c
	gcc -c -g strings_words_symbols.c

strings_words_symbols_test.o: strings_words_symbols.h strings_words_symbols_test.c
	gcc -c -g strings_words_symbols_test.c

a.out: mystring.o strings_words_symbols.o strings_words_symbols_test.o
	gcc -o  a.out mystring.o strings_words_symbols.o strings_words_symbols_test.o

do-test: a.out
	valgrind ./a.out -g

clean: mystring.o strings_words_symbols.o strings_words_symbols_test.o a.out
	rm mystring.o strings_words_symbols.o strings_words_symbols_test.o a.out
