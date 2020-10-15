all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
system.o: ../lib/umath.h system.h system.c
	gcc -c system.c
test.o: ../lib/umath.h system.h test.c
	gcc -c test.c

a.out: umath.o system.o test.o
	gcc -g -o a.out umath.o system.o test.o -lm
do-test: a.out
	./a.out

clean: umath.o system.o test.o
	rm -rf *.o
