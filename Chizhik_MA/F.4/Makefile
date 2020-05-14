all: do-test clean

getnames.o: printdiff.h getnames.h getnames.c
	gcc -c getnames.c
printdiff.o: printdiff.h printdiff.c
	gcc -c printdiff.c
test.o: printdiff.h test.c
	gcc -c test.c

run: printdiff.o getnames.o test.o
	gcc -o run printdiff.o getnames.o test.o
do-test: run
	valgrind ./run dir1 dir2 output.txt
	cat output.txt

clean: printdiff.o getnames.o test.o
	rm -rf *.o
