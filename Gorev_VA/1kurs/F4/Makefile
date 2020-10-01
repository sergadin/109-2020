all: do-test clear

do-test: a.out
	valgrind ./a.out dir1 dir2

a.out: file.o prog.o
	gcc -c file.c
	gcc -c prog.c
	gcc prog.o file.o -lm

clear:
	rm prog.o file.o a.out
