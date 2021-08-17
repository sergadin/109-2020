all:do-test clean

prog3-6.o: prog3-6.c prog3-6.h
	gcc -c prog3-6.c

test.o: test.c prog3-6.h
	gcc -c test.c

a.out: test.o prog3-6.o
	gcc test.o prog3-6.o -lm

do-test: a.out
	./a.out

clean: test.o prog3-6.o
	rm test.o prog3-6.o
