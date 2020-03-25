all: do-test clean

inte.o: inte.c inte.h
#	gcc -c inte.c

test.o: test.o inte.h
#	gcc -c test.c

a.out: test.o inte.o
	gcc test.o inte.o

do-test: a.out
	./a.out

clean: test.o inte.o
	rm test.o inte.o
