all: do-test clean

planner.o: planner.hpp planner.cpp
	g++ -c planner.cpp
test.o: planner.hpp test.cpp
	g++ -c test.cpp

run: planner.o test.o
	g++ -o run planner.o test.o
do-test: run
	valgrind ./run
clean: planner.o test.o
	cat output.txt
	rm -rf *.o vgcore.* run
