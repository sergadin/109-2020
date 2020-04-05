prog.out: main.o test.o solve.o
	gcc main.o test.o solve.o -o prog.out
main.o: main.c test.h solve.h
	gcc -c main.c
solve.o: solve.c solve.h test.h
	gcc -c solve.c
test.o: test.c test.h
	gcc -c test.c