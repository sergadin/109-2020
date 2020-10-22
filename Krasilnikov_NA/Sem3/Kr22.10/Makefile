all: do-test clean

IntSet.o: matrix.cpp
	g++ -c -g matrix.cpp
test.o: test.cpp
	g++ -c -g test.cpp
a.out: matrix.o test.o
	g++ test.o matrix.o
do-test: a.out
	valgrind ./a.out
clean:
	rm -rf *.o
