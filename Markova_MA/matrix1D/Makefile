CFLAGS = -c -g -Wall -O3

start: a.out

f.o: typedef.h
	gcc $(CFLAGS) f.c -o f.o

main.o: typedef.h f.o
	gcc $(CFLAGS) main.c -o main.o

a.out: f.o main.o e1.o
	gcc f.o main.o e1.o -o a.out

e1.o: typedef.h f.o
	gcc $(CFLAGS) e1.c -o e1.o

cl:
	rm -f *.o
	rm -f *.out