CC=gcc
CFLAGS = -Wall -O3
prog.out: 12.o tests12.o
	gcc 12.o tests12.o -lm -o prog.out
12.o: 12.h 12.c  
tests12.o: 12.h tests12.c
clean:
	rm -f prog.out tests12.o 12.o

