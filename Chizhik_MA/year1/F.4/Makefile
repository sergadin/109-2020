all: do-test clean

finddiff.o: finddiff.h finddiff.c
	gcc -c finddiff.c
test.o: finddiff.h test.c
	gcc -c test.c

run: finddiff.o test.o
	gcc -o run finddiff.o test.o
do-test: run
	valgrind ./run dir1 dir2 output.txt
	cat output.txt

clean: finddiff.o test.o
	rm -rf *.o
