all: do-test clean

umath.o: ../lib/umath.c ../lib/umath.h
	gcc -c ../lib/umath.c
secant.o: secant.c secant.h ../lib/umath.h
	gcc -c secant.c
test.o: test.c secant.h ../lib/umath.h
	gcc -c test.c
a.out: secant.o test.o umath.o
	gcc -o a.out test.o secant.o umath.o

do-test: a.out
	./a.out

clean: secant.o test.o umath.o
	rm secant.o umath.o test.o
