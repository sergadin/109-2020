all: do-test

determinant.o: determinant.c determinant.h
	gcc -c determinant.c

test.o: test.c determinant.h
	gcc -c test.c

a.out: test.o determinant.o
	gcc test.o determinant.o

do-test: a.out
	./a.out
	
