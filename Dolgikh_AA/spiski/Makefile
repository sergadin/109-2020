all: do-test clean

class.o: main.cpp
	g++ -c main.cpp

a.out: main.o
	g++ main.o

do-test: a.out
	valgrind ./a.out

clean: main.o
	rm main.o a.out
