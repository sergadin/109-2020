all: do-test clean

vector_clock.o: vector_clock.cpp
	g++ -c vector_clock.cpp

main.o: main.cpp
	g++ -c main.cpp

run: vector_clock.o main.o
	g++ -o run main.o vector_clock.o -lm

do-test: run
	./run
clean: 
	rm -rf *.o
