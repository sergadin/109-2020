all: do-test 

bisec.o: bisec.c bisec.h
	gcc -c bisec.c

test.o: test.c bisec.h
	gcc -c test.c

a.out: test.o bisec.o
	gcc test.o bisec.o

do-test: a.out
	./a.out
	
clean: test.o bisec.o
	rm test.o bisec.o
