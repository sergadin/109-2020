CFLAGS = -c -Wall -O3
prog.out: 1_.o 
	gcc 1_.o func_.o -lm -o prog.out 
1_.o: func.h func_.o 
	gcc $(CFLAGS) 1.c -o 1_.o 
func_.o: func.h
	gcc $(CFLAGS) func.c -o func_.o
clean:
	rm -f prog.out 1_.o func_.o 
