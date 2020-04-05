all: do-test clear

do-test: a.out
	./a.out

int.o: int.cpp int.hpp
	g++ -c int.cpp

test.o: test.cpp int.hpp
	g++ -c -lm test.cpp

a.out: test.o int.o
	g++ int.o test.o -lm

clear:
	rm int.o test.o a.out
