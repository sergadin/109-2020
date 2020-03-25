all: do-test 

scalar.o: scalar.c scalar.h
	gcc -c scalar.c

test.o: test.c scalar.h
	gcc -c test.c

a.out: test.o scalar.o
	gcc test.o scalar.o

do-test: a.out
	./a.out
	
clean: test.o scalar.o
	rm test.o scalar.o
