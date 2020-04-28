all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
ustrings.o: ../lib/ustrings.h ../lib/ustrings.c
	gcc -c ../lib/ustrings.c
determinant.o: ../lib/ustrings.h ../lib/umath.h determinant.h determinant.c
	gcc -c determinant.c
test.o: ../lib/ustrings.h determinant.h test.c
	gcc -c test.c
a.out: ustrings.o umath.o determinant.o test.o
	gcc -o a.out ustrings.o umath.o determinant.o test.o

do-test: a.out
	valgrind ./a.out
	diff -y output.txt answer.txt
	echo "There're no differences"
clean: ustrings.o umath.o determinant.o test.o
	rm -rf *.o
