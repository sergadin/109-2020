all: do-test clean

test.o: test.cpp
	g++ -c test.cpp

run: test.o
	g++ -o run test.o -lm

do-test: run
	valgrind ./run
clean: 
	rm -rf *.o