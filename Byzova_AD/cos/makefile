CC=gcc
CFLAGS = -Wall -O3
prog.out: 4.o tests4.o
	gcc 4.o tests4.o -lm -o prog.out
4.o: 4.h 4.c  
tests4.o: 4.h tests4.c
clean:
	rm -f prog.out tests4.o 4.o


