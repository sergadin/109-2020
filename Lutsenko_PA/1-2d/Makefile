all: do-test clean 


1.o: 1.c 1.h
#     gcc -c 1.c

1test.o: 1test.c 1.h
#     gcc -c 1test.c

a.out: 1test.o 1.o
	gcc 1test.o 1.o

do-test: a.out
	./a.out
