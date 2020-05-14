all: do-test

rank.o: rank.c rank.h
	gcc -c rank.c

test.o: test.c rank.h
	gcc -c test.c

a.out: test.o rank.o
	gcc test.o rank.o

do-test: a.out
	./a.out
