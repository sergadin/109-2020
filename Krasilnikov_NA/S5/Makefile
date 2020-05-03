all: do-test clean

mystring.o: ../libs/mystring.h ../libs/mystring.c
	gcc -c ../libs/mystring.c

format.o: ../libs/mystring.h format.h format.c
	gcc -c format.c

format_test.o: format.h format_test.c
	gcc -c format_test.c

a.out: mystring.o format.o format_test.o
	gcc -o a.out mystring.o format.o format_test.o

do-test: a.out
	valgrind -v --leak-check=full ./a.out 

clean: mystring.o format.o format_test.o a.out
	rm mystring.o format.o format_test.o a.out
