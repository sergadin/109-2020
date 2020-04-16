all: do-test clean

f.o: f.cpp
	g++ -c f.cpp
test.o: test.cpp
	g++ -c test.cpp
run: f.o test.o
	g++ -o run f.o test.o -lm

do-test: run
	./run
clean: 
	rm -rf *.o
