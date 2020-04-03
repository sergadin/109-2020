all: do-test clear

do-test: a.out
	./a.out

a.out: file.o appr.o
	g++ -c appr.c
	g++ -c appr.c
	g++ appr.o file.o -lm

clear:
	rm appr.o file.o a.out