all: do-test

replace.o: replace.c replace.h
	gcc -c replace.c

test.o: test.c replace.h
	gcc -c test.c

a.out: test.o replace.o
	gcc test.o replace.o

do-test: a.out
	./a.out


	
