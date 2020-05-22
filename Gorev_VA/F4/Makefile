all: do-test clear

do-test: a.out
	valgrind ./a.out dir1 dir2

a.out: det.o file.o
	gcc -c prog.c
	gcc -c file.c
	gcc prog.o file.o -lm

clear:
	rm prog.o file.o a.out