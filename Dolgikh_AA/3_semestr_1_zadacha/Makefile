all: do-test clean

Lamport.o: Lamport.cpp
	g++ -c Lamport.cpp

test.o: test.cpp
	g++ -c test.cpp

a.out: Lamport.o test.o
	g++ test.o Lamport.o

do-test: a.out
	./a.out

clean: Lamport.o test.o
	rm Lamport.o test.o
