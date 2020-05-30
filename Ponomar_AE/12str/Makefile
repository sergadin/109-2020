CFLAGS = -c -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations -Wdeclaration-after-statement -fsanitize=address -g

all: do-test clean

indent.o: indent.h indent.c
	gcc $(CFLAGS) indent.c

test.0: indent.h indent.c
	gcc $(CFLAGS) test.c

a.out: indent.o test.o
	gcc -o a.out indent.o test.o

do-test: a.out
	valgrind ./a.out

clean: indent.o test.0 a.out
	rm indent.o test.o a.out

