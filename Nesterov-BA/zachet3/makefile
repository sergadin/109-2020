all:do-test clean

zachet3.o: zachet3.c zachet3.h
	gcc -c zachet3.c

testzach.o: testzach.c zachet3.h
	gcc -c testzach.c

a.out: testzach.o zachet3.o
	gcc testzach.o zachet3.o -lm

do-test: a.out
	./a.out

clean: testzach.o zachet3.o
	rm testzach.o zachet3.o
