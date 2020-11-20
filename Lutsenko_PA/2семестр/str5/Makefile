all: do-test clean 


5.o: 5.c 5.h
#     gcc -c 5.c

5test.o: 5test.c 5.h
#     gcc -c 5test.c

a.out: 5test.o 5.o
	gcc 5test.o 5.o

do-test: a.out 
	./a.out
