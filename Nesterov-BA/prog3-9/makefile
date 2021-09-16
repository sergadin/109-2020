all:do-test clean

prog3-9.o: prog3-9.c prog3-9.h
	gcc -c prog3-9.c

test.o: test.c prog3-9.h
	gcc -c test.c

a.out: test.o prog3-9.o
	gcc test.o prog3-9.o -lm

do-test: a.out
	./a.out

clean: test.o prog3-9.o
	rm test.o prog3-9.o
