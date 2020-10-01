all: do-test clean
sets.o: sets.hpp sets.cpp
	g++ -c sets.cpp
test.o: sets.hpp test.cpp
	g++ -c test.cpp
run: sets.o test.o
	g++ -o run sets.o test.o

do-test: run
	valgrind ./run
clean: sets.o test.o
	rm -rf *.o
