all: do_it clean

prog.o: prog.c help.h
	gcc -c prog.c

test.o: test.c help.h
	gcc -c test.c

a.out: prog.o test.o
	gcc prog.o test.o -lm

do_it: a.out
	./a.out

clean:  test.o prog.o
	rm test.o prog.o a.out
