all: do-test clean 


2.o: 2.c 2.h
#     gcc -c 2.c

2test.o: 2test.c 2.h
#     gcc -c 2test.c

a.out: 2test.o 2.o
	gcc 2test.o 2.o

do-test: a.out
	./a.out
