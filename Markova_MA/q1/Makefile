all: do-test clean

text.o: text.cpp
	g++ -c text.cpp
test.o: test.cpp
	g++ -c test.cpp
run: text.o test.o
	g++ -o run test.o text.o -lm
do-test: run
	./run
clean: 
	rm -rf *.o