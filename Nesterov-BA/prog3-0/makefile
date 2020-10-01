all: do_it clean

prog3-0.o: prog3-0.c prog3-0.h
	gcc -c prog3-0.c

test.o: test.c prog3-0.h
	gcc -c test.c

a.out: prog3-0.o test.o
	gcc prog3-0.o test.o -lm

do_it: a.out
	./a.out

clean:  test.o prog3-0.o
	rm test.o prog3-0.o a.out
