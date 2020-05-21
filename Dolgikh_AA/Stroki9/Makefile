all: do_include clean

do_include: a.out
	valgrind ./a.out

a.out: stroki.o func.o
	gcc stroki.o func.o

stroki.o: stroki.c func.h
	gcc -c stroki.c

func.o: func.c func.h
	gcc -c func.c

clean: stroki.o func.o
	rm stroki.o func.o
