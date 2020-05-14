all: do-test clean

printdiff.o: printdiff.h printdiff.c
	gcc -c printdiff.c
test.o: printdiff.h test.c
	gcc -c test.c

run: printdiff.o test.o
	gcc -o run printdiff.o test.o
do-test: run
	valgrind ./run dir1 dir2 output.txt
	cat output.txt

clean: printdiff.o test.o
	rm -rf *.o
