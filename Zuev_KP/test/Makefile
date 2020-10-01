all: do-test clean

func.o: intset.cpp
#	g++ -c intset.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o intset.o
	g++ test.o intset.o -lm

do-test: a.out
	./a.out

clean: test.o intset.o
	rm test.o intset.o
