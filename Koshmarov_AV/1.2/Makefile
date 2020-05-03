all: do_it clean

root.o: root.c help.h
	gcc -c root.c

test.o: test.c help.h
	gcc -c test.c

next_point.o: next_point.c help.h
	gcc -c next_point.c

a.out: next_point.o root.o test.o
	gcc next_point.o root.o test.o -lm

do_it: a.out
	./a.out

clean:  test.o root.o
	rm test.o root.o next_point.o a.out
