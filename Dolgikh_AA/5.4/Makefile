all: do-test clean

do-test: a.out
	./a.out

a.out: test.o
	g++ -c test.cpp
	g++ test.o -lm

clean:
	rm test.o a.out
