all: do-test clean

mystring.o: ../lib/mystring.h ../lib/mystring.c
	gcc -c ../lib/mystring.c

fromat.o: ../lib/mystring.h fromat.h fromat.c
	gcc -c fromat.c

fromat_test.o: fromat.h fromat_test.c
	gcc -c fromat_test.c

a.out: mystring.o fromat.o fromat_test.o
	gcc -o a.out mystring.o fromat.o fromat_test.o

do-test: a.out
	valgrind ./a.out

clean: mystring.o fromat.o fromat_test.o
	rm mystring.o fromat.o fromat_test.o
