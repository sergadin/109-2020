all: a.out
zachet1.o: zachet1.c
	gcc -std=c99 -c zachet1.c -o zachet1.o -lm
func.o: func.c
	gcc -std=c99 -c func.c -o func.o -lm
a.out: zachet1.o func.o
	gcc zachet1.o func.o -lm
clean:
	rm -rf *.o
