all:do-test clean

prog1-2.o: prog1-2.c prog1-2.h
	gcc -c prog1-2.c

test.o: test.c prog1-2.h
	gcc -c test.c

a.out: test.o prog1-2.o
	gcc test.o prog1-2.o -lm

do-test: a.out
	./a.out

clean: test.o prog1-2.o
	rm test.o prog1-2.o
