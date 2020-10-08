all: do-test clear

do-test: a.out
	valgrind ./a.out

a.out: intset.o test.o
	g++ -c intset.cpp
	g++ -c test.cpp
	g++ intset.o test.o -lm

clear:
	rm intset.o test.o a.out