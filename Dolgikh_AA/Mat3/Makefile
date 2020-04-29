all: do-test clean

task.o: task.c task.h
	gcc -c task.c

test.o: test.c task.h
	gcc -c test.c

a.out: task.o test.o
	gcc task.o test.o -lm

do-test: a.out
	./a.out

clean: task.o test.o
	rm task.o test.o
