all: do-test

f.o: f.c f.h
	gcc f.c -lm

test.o: test.o f.h
	gcc -c test.c

a.out: test.o f.o
	gcc test.o f.o -lm

do-test: a.out
	./a.out