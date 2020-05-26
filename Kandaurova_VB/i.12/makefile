all: do-test clear

do-test: a.out
	./a.out

find.o: find.c find.h
	gcc -c find.c

test.o: test.c find.h
	gcc -c -lm test.c

a.out: test.o find.o
	gcc find.o test.o -lm

clear:
	rm find.o test.o a.out
