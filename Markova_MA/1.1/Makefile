all: run
test_sum.o: test_sum.c
	gcc -std=c99 -c test_sum.c -o test_sum.o -lm
sum.o: sum.c
	gcc -std=c99 -c sum.c -o sum.o -lm
run: test_sum.o sum.o
	gcc -o run test_sum.o sum.o -lm
clean:
	rm -rf *.o