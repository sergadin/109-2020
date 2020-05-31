CC=gcc
CFLAGS=-g

all: do-test clean

tree.o: tree.h tree.c
	gcc -c -g tree.c

tree_test.o: tree.h tree_test.c
	gcc -c -g tree_test.c

a.out: tree.o tree_test.o
	gcc -o a.out tree.o tree_test.o

do-test: a.out
	valgrind ./a.out ../../Krasilnikov_NA output.txt

clean: tree.o tree_test.o
	rm -rf *.o
