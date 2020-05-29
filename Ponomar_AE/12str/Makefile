all: do-test

indent.o: indent.c indent.h
	gcc -c indent.c

test.o: test.c indent.h
	gcc -c test.c

a.out: test.o indent.o
	gcc test.o indent.o

do-test: a.out
	./a.out
