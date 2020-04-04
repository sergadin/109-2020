all: do-test clear

do-test: a.out
	./a.out

log.o: log.c log.h
	gcc -c log.c

test.o: test.c log.h
	gcc -c -lm test.c

a.out: test.o log.o
	gcc log.o test.o -lm

clear:
	rm log.o test.o a.out