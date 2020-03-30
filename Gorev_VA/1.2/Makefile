all: do-test clear

do-test: a.out
	./a.out

a.out: file.o root.o
	gcc -c file.cpp
	gcc -c root.cpp
	gcc root.o file.o

clear:
	rm root.o file.o a.out