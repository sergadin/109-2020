all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
taylor.o: ../lib/umath.h taylor.h taylor.c
	gcc -c taylor.c
test.o: ../lib/umath.h taylor.h test.c
	gcc -c test.c
a.out: umath.o taylor.o test.o
	gcc -Wall -Wextra -Werror -Wold-style-declaration -Wold-style-definition \
    -Wfloat-equal -pedantic -std=c99 -o a.out umath.o taylor.o test.o -lm

do-test: a.out
	./a.out
clean: umath.o taylor.o test.o
	rm umath.o taylor.o test.o
