all: do-test clean

test_int.o: intset.o intset.h

a.out: intset.o
	g++ intset.o

do-test: a.out
	./a.out

clean:
	rm intset.o
	
