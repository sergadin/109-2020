all: do - test
inte.o: inte.c inte.h
	gcc -c inte.c
testinte.o: testinte.c inte.h
	gcc -c testinte.c
a.out: testinte.o inte.o
	gcc testinte.o inte.o
do - test: a.out
	./a.out
