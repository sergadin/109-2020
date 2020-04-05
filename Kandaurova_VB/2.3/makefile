all: do-test clear

do-test: a.out
	./a.out

log.o: simp.c simp.h
	gcc -c simp.c

test.o: test.c simp.h
	gcc -c -lm test.c

a.out: test.o simp.o
	gcc simp.o test.o -lm

clear:
	rm simp.o test.o a.out
