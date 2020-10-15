all: do-test clear

do-test: a.out
	valgrind ./a.out

a.out: list.o test.o
	g++ -c list.cpp
	g++ -c test.cpp
	g++ list.o test.o -lm

clear:
	rm list.o test.o a.out
