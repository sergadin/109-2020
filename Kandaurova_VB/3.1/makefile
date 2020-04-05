all: do-test clear

do-test: a.out
	./a.out

log.o: geom.c geom.h
	gcc -c geom.c

test.o: test.c geom.h
	gcc -c -lm test.c

a.out: test.o geom.o
	gcc geom.o test.o -lm

clear:
	rm geom.o test.o a.out
