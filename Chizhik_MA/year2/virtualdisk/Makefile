all: do-test clean

disk.o: disk.hpp disk.cpp
	g++ -c disk.cpp
test.o: disk.hpp test.cpp
	g++ -c test.cpp
run: disk.o test.o
	g++ -o run disk.o test.o

do-test: run
	valgrind ./run
	#./run
clean: disk.o test.o
	rm -rf vgcore.* run *.o
