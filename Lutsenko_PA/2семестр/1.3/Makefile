all: do-test clean 


13.o: 13.c 13.h
#     gcc -c 13.c

13test.o: 13test.c 13.h
#     gcc -c 13test.c

a.out: 13test.o 13.o
	gcc 13test.o 13.o

do-test: a.out
	./a.out
