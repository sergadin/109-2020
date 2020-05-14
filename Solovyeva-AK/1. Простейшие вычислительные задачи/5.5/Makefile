all: do-test clean

rms_approximation.o: rms_approximation.cpp
	g++ -c rms_approximation.cpp
test.o: test.cpp
	g++ -c test.cpp
run: rms_approximation.o test.o
	g++ -o run test.o rms_approximation.o -lm
do-test: run
	./run
clean: 
	rm -rf *.o
