all: do-test clear

do-test: a.out
	./a.out

a.out: inverse.o file.o
	gcc -c inverse.c
	gcc -c file.c
	gcc inverse.o file.o -lm

clear:
	rm inverse.o file.o a.out