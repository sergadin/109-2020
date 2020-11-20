all: do-test clean 


4.o: 4.c 4.h
#     gcc -c 4.c

4test.o: 4test.c 4.h
#     gcc -c 4test.c

a.out: 4test.o 4.o
	gcc 4test.o 4.o

do-test: a.out
	./a.out
