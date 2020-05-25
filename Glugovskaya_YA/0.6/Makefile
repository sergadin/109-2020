prog.out: test.o solve.o
	gcc test.o solve.o -o prog.out -lm
solve.o: solve.c solve.h
	gcc -c solve.c
