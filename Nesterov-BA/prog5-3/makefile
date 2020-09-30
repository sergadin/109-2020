all:do-test clean

prog5-3.o: prog5-3.c prog5-3.h
	gcc -c prog5-3.c

test.o: test.c prog5-3.h
	gcc -c test.c

a.out: test.o prog5-3.o
	gcc test.o prog5-3.o -lm

do-test: a.out
	./a.out

clean: test.o prog5-3.o
	rm test.o prog5-3.o
