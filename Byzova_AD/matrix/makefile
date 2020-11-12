all: do-test clean


a.out: matrix.o test.o
	g++ -c matrix.cpp
	g++ -c test.cpp
	g++ matrix.o test.o -lm

do-test: a.out
	./a.out
clean:
	rm -f matrix.o test.o a.out
