all: do-test clear

do-test: a.out
	./a.out

a.out: file.o appr.o
	gcc -c appr.c
	gcc -c appr.c
	gcc appr.o file.o -lm

clear:
	rm appr.o file.o a.out