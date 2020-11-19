all: do-test clean

matrix.o: matrix.cpp
	g++ -c matrix.cpp
	
test.o: test.cpp
	g++ -c test.cpp

a.out: matrix.o test.o
	g++  test.o matrix.o 

do-test: a.out
	./a.out

clean: matrix.o test.o
	rm matrix.o test.o
