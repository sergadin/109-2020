all: do-test clean

IntSet.o: IntSet.cpp
	g++ -c IntSet.cpp
test.o: test.cpp
	g++ -c test.cpp
a.out: IntSet.o test.o
	g++ test.o IntSet.o 
do-test: a.out
	./a.out
clean: 
	rm -rf *.o
