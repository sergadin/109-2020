all: do-test clear

do-test: a.out
	valgrind ./a.out

a.out: sort.o file.o
	gcc -c sort.c
	gcc -c file.c
	gcc sort.o file.o -lm

clear:
	rm sort.o file.o a.out