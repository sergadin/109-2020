all: a.out
zachet1.o: zachet1.c
	gcc -std=c99 -c zachet1.c -o zachet1.o -lm
a.out: zachet1.o
	gcc zachet1.o -lm
clean:
	rm -rf *.o
