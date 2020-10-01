all: do-test 

integral.o: integral.c integral.h
	gcc -c integral.c

test.o: test.c integral.h
	gcc -c test.c

a.out: test.o integral.o
	gcc test.o integral.o

do-test: a.out
	./a.out
	
clean: test.o integral.o
	rm test.o integral.o
