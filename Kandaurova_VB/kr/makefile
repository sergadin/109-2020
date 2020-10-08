all: do-test clear

do-test: a.out
	./a.out

cl.o: cl.h cl.cpp
	g++ -c cl.cpp

test.o: cl.h test.cpp
	g++ -c test.cpp

a.out: cl.o test.o
	g++ cl.o test.o

clear: cl.o test.o
	rm test.o cl.o
