all: do-test
map.o: map.h map.c
	gcc -c map.c
test.o: map.h map.c test.c
	gcc -c test.c
a.out: test.o map.o
	gcc -o a.out map.o test.o
do-test: a.out
	./a.out
