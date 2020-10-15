all: do-test clean

func.o: stack.cpp
#	g++ -c stack.cpp

test.o: test.cpp
#	g++ -c test.cpp

a.out: test.o stack.o
	g++ test.o stack.o -lm

do-test: a.out
	./a.out

clean: test.o stack.o
	rm test.o stack.o
