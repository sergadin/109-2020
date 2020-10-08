a.out: main.o solve.o prn_matr.o
	gcc main.o solve.o prn_matr.o -o a.out -lm
main.o: main.c solve.h  prn_matr.h 
	gcc -c main.c
solve.o: solve.c solve.h prn_matr.h
	gcc -c solve.c
prn_matr.o: prn_matr.c prn_matr.h
	gcc -c prn_matr.c
