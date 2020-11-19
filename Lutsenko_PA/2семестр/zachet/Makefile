all: do-test clean 


zachet.o: zachet.c zachet.h
#     gcc -c zachet.c

zachet_test.o: zachet_test.c zachet.h
#     gcc -c zachet_test.c

a.out: zachet_test.o zachet.o
	gcc zachet_test.o zachet.o

do-test: a.out
	./a.out
