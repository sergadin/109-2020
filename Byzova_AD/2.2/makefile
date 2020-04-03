CFLAGS = -c -Wall -O3
prog.out: 2_.o 
	gcc 2_.o tests2_.o -lm -o prog.out
2_.o: 2.h tests2_.o 
	gcc $(CFLAGS) 2.c -o 2_.o 
tests2_.o: 2.h
	gcc $(CFLAGS) tests2.c -o tests2_.o
clean:
	rm -f prog.out 2_.o tests2_.o  

