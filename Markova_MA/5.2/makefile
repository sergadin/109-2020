all: do-test clean

test.o: 5.o 5.h
#	g++ -c 5.cpp

a.out: 5.o
	g++ 5.o

do-test: a.out
	./a.out

clean: 5.o 5.h
	rm 5.o 