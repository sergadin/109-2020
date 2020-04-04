all: do-test clear

do-test: a.out
	./a.out

a.out: file.o trap_sum.o
	gcc -c trap_sum.c
	gcc -c file.c
	gcc trap_sum.o file.o - lm

clear:
	rm trap_sum.o file.o a.out
