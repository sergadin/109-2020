all: do-test clean

ustrings.o: ../lib/ustrings.h ../lib/ustrings.c
	gcc -c ../lib/ustrings.c
word.o: ../lib/ustrings.h word.h word.c
	gcc -c word.c
test.o: word.h test.c
	gcc -c test.c

a.out: ustrings.o word.o test.o
	gcc -o a.out ustrings.o word.o test.o

do-test: a.out
	./a.out
	valgrind ./a.out
	diff -y answer.txt output.txt
	echo "There're no differences"

clean: ustrings.o word.o test.o
	rm -rf *.o
