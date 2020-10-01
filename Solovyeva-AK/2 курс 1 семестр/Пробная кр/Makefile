all: do-test clean

solution.o: solution.cpp
	g++ -c solution.cpp
test.o: test.cpp
	g++ -c test.cpp
run: solution.o test.o
	g++ -o run test.o solution.o -lm
do-test: run
	./run
clean: 
	rm -rf *.o
