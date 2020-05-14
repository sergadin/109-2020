all: do-test clean 


22.o: 22.c 22.h
#     gcc -c 22.c

22test.o: 22test.c 22.h
#     gcc -c 22test.c

a.out: 22test.o 22.o
	gcc 22test.o 22.o

do-test: a.out
	./a.out
