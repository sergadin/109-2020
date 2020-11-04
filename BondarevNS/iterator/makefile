all: do-test clean

iterator.o: iterator.cpp
	g++ -c -g iterator.cpp

test.o: test.cpp
	g++ -c -g test.cpp

a.out: iterator.o test.o
	g++ test.o iterator.o

do-test: a.out
	valgrind ./a.out

clean: iterator.o test.o
	rm iterator.o test.o