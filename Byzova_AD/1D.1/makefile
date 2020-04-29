CC=gcc
CFLAGS = -Wall -O3
prog.out: 1.o tests1.o
	gcc 1.o tests1.o -lm -o prog.out
1.o: 1.h 1.c  
tests1.o: 1.h tests1.c
clean:
	rm -f prog.out tests1.o 1.o
