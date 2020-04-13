1.exe: main.o read_matr.o solve.o prn_matr.o MaxEl.o
	gcc main.o read_matr.o solve.o prn_matr.o MaxEl.o -o 1.exe -lm
main.o: main.c read_matr.h solve.h  prn_matr.h 
	gcc -c main.c
read_matr.o: read_matr.c read_matr.h
	gcc -c read_matr.c
solve.o: solve.c solve.h MaxEl.h prn_matr.h
	gcc -c solve.c
prn_matr.o: prn_matr.c prn_matr.h
	gcc -c prn_matr.c
MaxEl.o: MaxEl.c MaxEl.h
	gcc -c MaxEl.c