all: do-test clean

func.o: kuslin.cpp
#	g++ -c kuslin.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o kuslin.o
	g++ test.o kuslin.o -lm

do-test: a.out
	./a.out

clean: test.o kuslin.o
	rm test.o kuslin.o
