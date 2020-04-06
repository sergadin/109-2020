FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations



prog: main.o sin.o
	gcc -lm $(FLAGS) -o prog -Wall main.o sin.o
main.o: main.c sin.h
	gcc $(FLAGS)  -c main.c
sin.o: sin.c sin.h
	gcc $(FLAGS)  -c sin.c

clean:
	rm -rf *.o 
