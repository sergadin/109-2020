all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
sequence.o: sequence.h ../lib/umath.h sequence.c
	gcc -c sequence.c
test.o: sequence.h ../lib/umath.h test.c
	gcc -c test.c
a.out: sequence.o umath.o test.o
	gcc -Wall -Wextra -Werror -Wold-style-declaration -Wold-style-definition \
    -Wfloat-equal -pedantic -std=c99 -o a.out umath.o test.o sequence.o

do-test: a.out
	./a.out

clean: sequence.o umath.o test.o
	rm sequence.o umath.o test.o
