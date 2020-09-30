all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
simpson.o: ../2.3/simpson.h ../2.3/simpson.c
	gcc -c ../2.3/simpson.c

solve.o: solve.h solve.c
	gcc -c solve.c
test.o: ../lib/umath.h ../2.3/simpson.h solve.h test.c
	gcc -c test.c

run: umath.o simpson.o solve.o test.o
	gcc -o run umath.o simpson.o solve.o test.o -lm
do-test: run
	valgrind ./run 4.5
	./run 50
	./run -5

clean: umath.o simpson.o solve.o
	rm -rf *.o
