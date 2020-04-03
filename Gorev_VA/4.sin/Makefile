all: do-test clear

do-test: a.out
	./a.out

a.out: file.o sin.o
	gcc -c sin.c
	gcc -c sin.c
	gcc sin.o file.o -lm

clear:
	rm sin.o file.o a.out