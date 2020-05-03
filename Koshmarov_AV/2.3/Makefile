all: do_it clean

simpson.o: simpson.c help.h
	gcc -c simpson.c

test.o: test.c help.h
	gcc -c test.c

a.out: simpson.o test.o help.h
	gcc simpson.o test.c

do_it: a.out
	./a.out

clean: test.o simpson.o
	rm test.o simpson.o a.out 
