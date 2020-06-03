CC=gcc
CFLAGS = -Wall -O3
prog.out: 5.o tests5.o
	gcc 5.o tests5.o -lm -o prog.out
5.o: 5.h 5.c  
tests5.o: 5.h tests5.c
clean:
	rm -f prog.out tests5.o 5.o
