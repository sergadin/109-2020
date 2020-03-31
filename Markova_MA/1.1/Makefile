all: do-test clear

do-test: a.out
	./a.out

a.out: test.o f.o
	gcc -c test.c
	gcc -c f.c
	gcc f.o test.o -lm

clear:
	rm f.o test.o a.out
