all: do-test clean

matr.o: matr.cpp
	g++ -c matr.cpp
test.o: test.cpp
	g++ -c test.cpp
run: matr.o test.o
	g++ -o run test.o matr.o -lm
do-test: run
	./run
clean: 
	rm -rf *.o
