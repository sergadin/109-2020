CC=gcc
CFLAGS=-g

all: do-test clean

test.o: test.cpp interpol.h
#	g++ -c test.cpp

a.exe: test.o
	g++ test.o

do-test: a.exe
	./a.exe

clean: test.o interpol.h
	rm test.o
