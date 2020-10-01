all: do-test clean

func.o: dasha.cpp 
#	g++ -c dasha.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o dasha.o
	g++ test.o dasha.o -lm

do-test: a.out
	./a.out

clean: test.o dasha.o
	rm test.o dasha.o
