all: do-test clean

umath.o: ../lib/umath.c ../lib/umath.h
	gcc -c ../lib/umath.c
map.o: map.h map.c
	gcc -c map.c
test.o: ../lib/umath.h map.h test.c
	gcc -c test.c
a.out: test.o map.o umath.o
	gcc -o a.out map.o umath.o test.o

do-test: a.out
	./a.out
clean: map.o umath.o test.o
	rm map.o umath.o test.o
