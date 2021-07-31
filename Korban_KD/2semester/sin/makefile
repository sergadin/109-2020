FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations



prog: main.o sin.o
	gcc  $(FLAGS) -o prog -Wall main.o sin.o -lm 
main.o: main.c sin.h
	gcc $(FLAGS)  -c main.c -lm 
sin.o: sin.c sin.h
	gcc $(FLAGS)  -c sin.c -lm 

clean:
	rm -rf *.o 
