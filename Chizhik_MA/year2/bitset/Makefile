all: do-test clean

bitset.o: bitset.hpp bitset.cpp
	g++ -c bitset.cpp
test.o: bitset.hpp test.cpp
	g++ -c test.cpp

run: bitset.o test.o
	g++ -o run bitset.o test.o

do-test: run
	valgrind ./run
	#./run
clean: bitset.o test.o
	rm -rf *.o
