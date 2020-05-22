all: do-test clear

do-test: a.out
	valgrind ./a.out dir1 dir2

a.out: file.o file1.o
	gcc -c file.c
	gcc -c file1.c
	gcc file1.o file.o -lm

clear:
	rm file1.o file.o a.out
