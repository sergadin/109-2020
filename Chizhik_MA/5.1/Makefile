all: do-test clean

umath.o: umath.h umath.cpp
	g++ -c umath.cpp
interpolation.o: interpolation.h umath.h interpolation.cpp
	g++ -c interpolation.cpp
test.o: interpolation.h umath.h test.cpp
	g++ -c test.cpp
a.out: interpolation.o umath.o test.o
	g++ -o a.out interpolation.o umath.o test.o -lm

do-test: a.out
	./a.out
clean: interpolation.o test.o umath.o
	rm interpolation.o test.o umath.o
