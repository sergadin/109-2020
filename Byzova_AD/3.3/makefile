CC=gcc
CFLAGS = -Wall -O3
prog.out: 3.o tests3.o
	gcc 3.o tests3.o -lm -o prog.out
3.o: 3.h 3.c  
tests3.o: 3.h tests3.c
clean:
	rm -f prog.out tests3.o 3.o
