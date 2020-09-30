CC=gcc
CFLAGS = -Wall -O3
prog.out: 13.o tests13.o
	gcc 13.o tests13.o -lm -o prog.out
13.o: 13.h 13.c  
tests13.o: 13.h tests13.c
clean:
	rm -f prog.out tests13.o 13.o

