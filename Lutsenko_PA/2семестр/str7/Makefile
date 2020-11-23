all: do-test clean 


7.o: 7.c 7.h
#     gcc -c 5.c

7test.o: 7test.c 7.h
#     gcc -c 7test.c

a.out: 7test.o 7.o
	gcc 7test.o 7.o

do-test: a.out 
	./a.out
