all: do_it clean

prog1-0.o: prog1-0.c prog1-0.h
	gcc -c prog1-0.c

test.o: test.c prog1-0.h
	gcc -c test.c

a.out: prog1-0.o test.o
	gcc prog1-0.o test.o -lm

do_it: a.out
	./a.out

clean:  test.o prog1-0.o
	rm test.o prog1-0.o a.out
