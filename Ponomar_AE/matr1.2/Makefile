all: do clean

rank.o: rank.h rank.c
        gcc -c rank.c
test.o: rank.h test.c
        gcc -c test.c
a.out: rank.o test.o
        gcc -o a.out test.c rank.o -lm
do: a.out
        ./a.out
clean:
	rm -rf *.o
~                                                                               
~                           
