all: do-test clean

class.o: class.cpp
	g++ -c class.cpp
	
test.o: test.cpp
	g++ -c test.cpp

a.out: class.o test.o
	g++  test.o class.o 

do-test: a.out
	./a.out

clean: class.o test.o
	rm class.o test.o
