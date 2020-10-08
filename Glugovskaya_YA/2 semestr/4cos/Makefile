prog.out: main.o f.o
	gcc main.o f.o -o prog.out
main.o: main.c f.h
	gcc -c main.c
f.o: f.c f.h
	gcc -c f.c