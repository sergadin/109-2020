all: do-test clean

func.o: vclock.cpp 
#	g++ -c vclock.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o vclock.o
	g++ test.o vclock.o -lm

do-test: a.out
	./a.out

clean: test.o vclock.o
	rm test.o vclock.o
