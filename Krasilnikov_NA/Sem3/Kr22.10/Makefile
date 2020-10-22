all: do-test clean

IntSet.o: Matrix.cpp
	g++ -c -g Maatrix.cpp
test.o: test.cpp
	g++ -c -g test.cpp
a.out: Maatrix.o test.o
	g++ test.o Maatrix.o
do-test: a.out
	valgrind ./a.out
clean:
	rm -rf *.o
