all: do-test clear

do-test: a.out
	valgrind ./a.out

a.out: clock.o test.o
	g++ -c clock.cpp
	g++ -c test.cpp
	g++ clock.o test.o -lm

clear:
	rm clock.o test.o a.out
