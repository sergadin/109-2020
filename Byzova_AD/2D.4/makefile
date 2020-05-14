CC=gcc
CFLAGS = -Wall -O3
prog.out: 2.o tests2.o
	gcc 2.o tests2.o -lm -o prog.out
2.o: 2.h 2.c  
tests2.o: 2.h tests2.c
clean:
	rm -f prog.out tests2.o 2.o
