all: do clean
solution.o: solution.c
	gcc -std=c99 -c solution.c -o solution.o -lm
generate.o: generate.c
	gcc -std=c99 -c generate.c -o generate.o -lm
run: solution.o generate.o
	gcc -o run generate.o solution.o -lm
do: run
	./run
clean:
	rm -rf *.o

