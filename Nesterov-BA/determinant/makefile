all:do-test clean

determinant.o: determinant.c determinant.h
	gcc -c determinant.c

test.o: test.c determinant.h
	gcc -c test.c

a.out: test.o determinant.o
	gcc test.o determinant.o -lm

do-test: a.out
	./a.out

clean: test.o determinant.o
	rm test.o determinant.o
