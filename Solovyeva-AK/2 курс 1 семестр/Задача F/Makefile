all: do-test clean

test.o: test.cpp
	g++ -c test.cpp
a.out: test.o
	g++ -g test.o 
do-test: a.out
	./a.out
clean: 
	rm -rf *.o
