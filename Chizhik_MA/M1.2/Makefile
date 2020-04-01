all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
determinant.o: determinant.h ../lib/umath.h determinant.c
	gcc -c determinant.c
test.o: determinant.h ../lib/umath.h test.c
	gcc -c test.c

a.out: umath.o determinant.o test.o
	gcc -Wall -Wextra -Werror -Wold-style-declaration -Wold-style-definition \
    -Wfloat-equal -pedantic -std=c99 -o a.out umath.o determinant.o test.o -lm
do-test: a.out
	./a.out

clean: umath.o determinant.o test.o
	rm -rf *.o
