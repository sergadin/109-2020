all: do-test clean

getdata.o: printdiff.h getdata.h getdata.c
	gcc -c getdata.c
printdiff.o: printdiff.h printdiff.c
	gcc -c printdiff.c
test.o: printdiff.h test.c
	gcc -c test.c

run: printdiff.o getdata.o test.o
	gcc -o run printdiff.o getdata.o test.o
do-test: run
	valgrind ./run dir1 dir2 output.txt
	cat output.txt

clean: printdiff.o getdata.o test.o
	rm -rf *.o
