a.out: main.o read.o print.o solve.o
	gcc main.o read.o print.o solve.o -o a.out -lm
main.o: main.c read.h print.h solve.h
	gcc -c main.c
read.o: read.c read.h solve.h print.h
	gcc -c read.c
solve.o: solve.c solve.h print.h
	gcc -c solve.c
print.o: print.c print.h
	gcc -c print.c

