all: do-test clean

umath.o: ../lib/umath.h ../lib/umath.c
	gcc -c ../lib/umath.c
secant.o: ../1.3/secant.h ../1.3/secant.c
	gcc -c ../1.3/secant.c
simpson.o: ../2.3/simpson.h ../2.3/simpson.c
	gcc -c ../2.3/simpson.c

solve.o: solve.h solve.c
	gcc -c solve.c
test.o: ../lib/umath.h ../1.3/secant.h ../2.3/simpson.h solve.h test.c
	gcc -c test.c

run: umath.o secant.o simpson.o solve.o test.o
	gcc -o run umath.o secant.o simpson.o solve.o test.o -lm
do-test: run
	valgrind ./run 50

clean: umath.o secant.o simpson.o solve.o
	rm -rf *.o
