CFLAGS = -c -Wall -O3
prog.out: 5_.o 
	gcc 5_.o tests5_.o -lm -o prog.out
5_.o: 5.h tests5_.o 
	gcc $(CFLAGS) 5.c -o 5_.o 
tests5_.o: 5.h
	gcc $(CFLAGS) tests5.c -o tests5_.o
clean:
	rm -f prog.out 5_.o tests5_.o  

