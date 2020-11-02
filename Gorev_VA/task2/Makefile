all: do-test clear

do-test: a.out
	valgrind ./a.out

a.out: node.o test.o
	g++ -c node.cpp
	g++ -c test.cpp
	g++ node.o test.o -lm

clear:
	rm node.o test.o a.out