all: do-test clean

ustrings.o: ../lib/ustrings.h ../lib/ustrings.c
	gcc -c ../lib/ustrings.c
task54.o: ../lib/ustrings.h task54.h task54.c
	gcc -c task54.c
test.o: task54.h test.c
	gcc -c test.c

a.out: ustrings.o task54.o test.o
	gcc -o a.out ustrings.o task54.o test.o
do-test: a.out
	valgrind ./a.out input.txt
	cat result.txt

clean: ustrings.o task54.o test.o
	rm -rf *.o
