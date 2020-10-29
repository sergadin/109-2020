all: do-test clean

iterator.o: iterator.cpp
g++ -c iterator.cpp

test.o: test.cpp
g++ -c test.cpp

a.out: iterator.o test.o
g++ test.o iterator.o

do-test: a.out
./a.out

clean: iterator.o test.o
rm iterator.o test.o