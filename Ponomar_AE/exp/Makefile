all: do-test 

exp.o: exp.c exp.h
	gcc -c exp.c

test.o: test.c exp.h
	gcc -c test.c

a.out: test.o exp.o
	gcc test.o exp.o -lm

do-test: a.out
	./a.out
	
clean: test.o exp.o
	rm test.o exp.o
