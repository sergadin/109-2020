1.exe: main.o f.o
	gcc -g main.o f.o -o 1.exe -lm
main.o: main.c f.h
	gcc -g -c main.c
f.o: f.c f.h
	gcc -g -c f.c