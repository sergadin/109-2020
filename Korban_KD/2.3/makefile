FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations

prog: ../lib/exmath.o test.o integration.o 
	gcc -lm $(FLAGS) test.o ../lib/exmath.o integration.o -o prog
../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc -lm $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o
test.o: test.c
	gcc -lm $(FLAGS) -c test.c
integration.o: integration.c integration.h
	gcc -lm $(FLAGS) -c integration.c 	

	
	
	
clean:
	rm -rf *.o 
