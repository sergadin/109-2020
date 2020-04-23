all: do-test clear

do-test: a.out
	./a.out

a.out: file.o inverse.o
	gcc -c file.c
	gcc -c inverse.c
	gcc inverse.o file.o -lm

clear:
	rm inverse.o file.o a.out