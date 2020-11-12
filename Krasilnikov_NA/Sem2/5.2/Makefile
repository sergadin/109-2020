all: do-test clean

test_int.o: test.o interpolation.h

a.out: test.o
	g++ test.o

do-test: a.out
	./a.out

clean:
	rm test.o
	
