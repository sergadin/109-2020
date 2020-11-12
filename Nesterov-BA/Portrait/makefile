all: do-test clean

profile.o: profile.cpp
	g++ -c profile.cpp
	
test.o: test.cpp
	g++ -c test.cpp

a.out: profile.o test.o
	g++  test.o profile.o 

do-test: a.out
	./a.out

clean: profile.o test.o
	rm profile.o test.o
