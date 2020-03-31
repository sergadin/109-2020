all: do-test clear

do-test: a.out
	./a.out

a.out: file.o min_value.o
	gcc -c min_value.c
	gcc -c min_value.c
	gcc min_value.o file.o

clear:
	rm min_value.o file.o a.out