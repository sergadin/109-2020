all: run
test.o: test.c
	gcc -std=c99 -c test.c -o test.o 
f.o: f.c
	gcc -std=c99 -c f.c -o f.o 
run: test.o f.o
	gcc -o run test.o f.o
clean: 
	rm -rf *.o
