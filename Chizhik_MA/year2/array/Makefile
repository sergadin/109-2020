all: do-test clean

test.o: dynarr.hpp test.cpp
	g++ -c test.cpp
run: test.o
	g++ -o run test.o

do-test: run
	valgrind ./run
clean: test.o
	rm -rf *.o
