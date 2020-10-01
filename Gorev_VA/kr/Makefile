all: do-test clear

do-test: a.out
	./a.out

a.out: intset.o test.o
	gcc -c intset.c
	gcc -c test.c
	gcc intset.o test.o -lm

clear:
	rm intset.o test.o a.out