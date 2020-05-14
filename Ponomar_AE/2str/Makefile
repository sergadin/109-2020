all: do-test

change.o: change.c change.h
	gcc -c change.c

test.o: test.c change.h
	gcc -c test.c

a.out: test.o change.o
	gcc test.o change.o

do-test: a.out
	./a.out
