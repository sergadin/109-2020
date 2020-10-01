all: do-test 

cos.o: cos.c cos.h
	gcc -c cos.c

test.o: test.c cos.h
	gcc -c test.c

a.out: test.o cos.o
	gcc test.o cos.o -lm

do-test: a.out
	./a.out
	
clean: test.o cos.o
	rm test.o cos.o
