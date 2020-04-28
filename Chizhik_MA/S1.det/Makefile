all: do-test clean

ustrings.o: ../lib/ustrings.h ../lib/ustrings.c
	gcc -c ../lib/ustrings.c
determinant.o: ../lib/ustrings.h determinant.h determinant.c
	gcc -c determinant.c
test.o: ../lib/ustrings.h determinant.h test.c
	gcc -c test.c
a.out: ustrings.o determinant.o test.o
	gcc -o a.out ustrings.o determinant.o test.o

do-test: a.out
	./a.out
clean: ustrings.o determinant.o test.o
	rm -rf *.o
