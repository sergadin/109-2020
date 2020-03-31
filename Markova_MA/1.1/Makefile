  
all: do-test clear

do-test: a.out
	./a.out

a.out: file.o root.o
	gcc -c file.c -lm
	gcc -c root.c -lm
	gcc root.o file.o -lm

clear:
	rm root.o file.o a.out