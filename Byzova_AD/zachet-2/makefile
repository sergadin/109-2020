CC=gcc
CFLAGS = -Wall -O3
prog.out: 52.o tests52.o
	gcc 52.o tests52.o -lm -o prog.out
52.o: 52.h 52.c  
tests52.o: 52.h tests52.c
clean:
	rm -f prog.out tests52.o 52.o
