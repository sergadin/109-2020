all: do-test clean

class.o: class.cpp
	g++ -c class.cpp

test.o: test.cpp
	g++ -c test.cpp

run: class.o test.o
	g++ -o run test.o class.o -lm

do-test: run
	valgrind ./run
clean: 
	rm -rf *.o