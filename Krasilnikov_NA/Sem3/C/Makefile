all: do-test clean

spisok.o: spisok.cpp
	g++ -c -g spisok.cpp
test.o: test.cpp
	g++ -c -g test.cpp
a.out: spisok.o test.o
	g++ test.o spisok.o
do-test: a.out
	valgrind ./a.out
clean:
	rm -rf *.o
