all: do-test clear

do-test: a.out
	 ./a.out

a.out: kr3.o test.o
	g++ -c kr3.cpp
	g++ -c test.cpp
	g++ kr3.o test.o -lm

clear:
	rm kr3.o test.o a.out
