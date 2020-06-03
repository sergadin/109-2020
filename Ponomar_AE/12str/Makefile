all: do-test clean

indent.o: indent.h indent.c
	gcc -c indent.c

test.0: indent.h indent.c
	gcc -c test.c

a.out: indent.o test.o
	gcc -o a.out indent.o test.o

do-test: a.out
	valgrind ./a.out

clean: indent.o test.0 a.out
	rm indent.o test.o a.out
