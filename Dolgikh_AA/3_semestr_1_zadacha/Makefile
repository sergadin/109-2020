all: do-test

Lamport.o: Lamport.cpp
	g++ -c Lamport.cpp

test.o: test.cpp
	g++ -c test.cpp

a.out: Lamport.o test.o
	g++ test.o Lamport.o

do-test: a.out
	./a.out
