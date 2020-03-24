<<<<<<< HEAD
all: do - test
inte.o: inte.c inte.h
	gcc -c inte.c
testinte.o: testinte.c inte.h
	gcc -c testinte.c
a.out: testinte.o inte.o
	gcc testinte.o inte.o
do - test: a.out
	./a.out
=======
CC=gcc
CFLAGS=-g

all: do-test clean

sum.o: func.c func.h
#	gcc -c func.c

sum_test.o: test.o func.h
#	gcc -c test.c

a.out: test.o func.o
	gcc test.o func.o

do-test: a.out
	./a.out

clean: test.o func.o
	rm test.o func.o
>>>>>>> 76ed227e4382bd0549084eb068794cfcdd37cf92
