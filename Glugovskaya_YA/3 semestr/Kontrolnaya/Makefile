all: do-test clean

func.o: Time.cpp 
	g++ -c Time.cpp

test.o: test.cpp
	g++ -c test.cpp

a.exe: test.o Time.o 
	g++ test.o Time.o -lm -o a.exe

do-test: a.exe
	./a.exe

clean: test.o Time.o
	rm test.o Time.o