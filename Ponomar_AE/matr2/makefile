all: do clean

determinant.o: determinant.h determinant.c
	gcc -c determinant.c
test.o: determinant.h test.c
	gcc -c test.c
a.out: determinant.o test.o
	        gcc -o a.out test.c determinant.o -lm
do: a.out
	./a.out
clean:
	rm -rf *.o
