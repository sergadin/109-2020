CFLAGS =-c -Wall -O3

prog.out: tests5.o
	g++ tests5.o -lm -o prog.out  
tests5.o: 5.h tests5.cpp
	g++ $(CFLAGS) tests5.cpp -lm -o tests5.o	
clean:
	rm -f prog.out tests5.o 
