all:do-test clean

task.o: task.c task.h
	gcc -c task.c

test.o: test.c task.h
	gcc -c test.c

a.out: test.o task.o
	gcc test.o task.o

do-test: a.out
	./a.out

clean: test.o task.o
	rm test.o task.o
