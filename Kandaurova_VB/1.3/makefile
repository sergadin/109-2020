all: do-test clear

do-test: a.out
	./a.out

log.o: chord.c chord.h
	gcc -c chord.c

test.o: test.c chord.h
	gcc -c -lm test.c

a.out: test.o chord.o
	gcc chord.o test.o -lm

clear:
	rm chord.o test.o a.out
