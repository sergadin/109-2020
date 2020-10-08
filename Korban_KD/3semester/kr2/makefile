 
a.out: test.o vector_clock.o 
	g++  test.o vector_clock.o  -o a.out 
test.o: test.c
	g++  -c test.c 
vector_clock.o: vector_clock.c vector_clock.h
	g++  -c vector_clock.c -o vector_clock.o 
