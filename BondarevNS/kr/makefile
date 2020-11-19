all: do-test clean

matr.o: matr.cpp
	g++ -c -g matr.cpp
test.o: test.cpp
	g++ -c -g test.cpp
a.out: matr.o test.o
	g++ test.o matr.o
do-test: a.out
	valgrind ./a.out
clean:
	rm -rf *.o
