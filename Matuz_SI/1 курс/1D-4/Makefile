all: do-test

gauss.o: gauss.c gauss.h
	gcc -c gauss.c

gauss_in_action.o: gauss_in_action.c gauss.h
	gcc -c gauss_in_action.c

a.out: gauss_in_action.o gauss.o
	gcc gauss_in_action.o gauss.o -lm

do-test: a.out
	./a.out
	
