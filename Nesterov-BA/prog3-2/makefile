all:do-test clean

prog3-2.o: prog3-2.c prog3-2.h
	gcc -c prog3-2.c

test.o: test.c prog3-2.h
	gcc -c test.c

a.out: test.o prog3-2.o
	gcc test.o prog3-2.o -lm

do-test: a.out
	./a.out

clean: test.o prog3-2.o
	rm test.o prog3-2.o
