all:do-test clean

gauss.o: gauss.c gauss.h
	gcc -c gauss.c

test.o: test.c gauss.h
	gcc -c test.c

a.out: test.o gauss.o
	gcc test.o gauss.o -lm

do-test: a.out
	./a.out

clean: test.o gauss.o
	rm test.o gauss.o
