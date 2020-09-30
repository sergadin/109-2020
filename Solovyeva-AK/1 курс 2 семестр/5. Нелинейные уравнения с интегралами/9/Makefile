all: run
9.o: 9.c
	gcc -std=c99 -c 9.c -o 9.o -lm
f.o: f.c
	gcc -std=c99 -c f.c -o f.o -lm
run: 9.o f.o
	gcc -o run 9.o f.o -lm
clean: 
	rm -rf *.o                  
