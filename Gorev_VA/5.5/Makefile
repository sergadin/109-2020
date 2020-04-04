all: do-test clear

do-test: a.out
	./a.out

a.out: file.o
	g++ -c file.cpp
	g++ file.o -lm

clear:
	rm file.o a.out
