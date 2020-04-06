all: do-test clean 


sum.o: sum.c sum.h
#     gcc -c sum.c

sum_test.o: test_sum.c sum.h
#     gcc -c test_sum.c

a.out: test_sum.o sum.o
	gcc test_sum.o sum.o

do-test: a.out
	./a.out
