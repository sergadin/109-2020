all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
simpson.o: simpson.h ../lib/umath.h simpson.c
	gcc -c simpson.c
test.o: simpson.h ../lib/umath.h test.c
	gcc -c test.c
a.out: simpson.o umath.o test.o
	gcc -Wall -Wextra -Werror -Wold-style-declaration -Wold-style-definition \
    -Wfloat-equal -pedantic -std=c99 -o a.out test.o simpson.o umath.o -lm

do-test: a.out
	./a.out

clean: simpson.o test.o umath.o
	rm simpson.o test.o umath.o
