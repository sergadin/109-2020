all: do-test clear

do-test: a.out
	./a.out

a.out: file.o
	g++ -c file.c
	g++ file.o -lm

clear:
	rm file.o a.out