all: do-test clear

do-test: a.out
	./a.out

a.out: det.o file.o
	gcc -c det.c
	gcc -c file.c
	gcc det.o file.o -lm

clear:
	rm det.o file.o a.out