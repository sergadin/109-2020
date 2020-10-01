all: do-test clean

func.o: matr.cpp 
#	g++ -c matr.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o matr.o
	g++ test.o matr.o -lm

do-test: a.out
	./a.out

clean: test.o matr.o
	rm test.o matr.o
