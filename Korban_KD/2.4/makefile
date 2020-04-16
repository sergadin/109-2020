FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations

prog: ../lib/exmath.o test.o integration.o 
	gcc  $(FLAGS) test.o ../lib/exmath.o integration.o -o prog -lm 
../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc  $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o -lm 
test.o: test.c
	gcc  $(FLAGS) -c test.c -lm 
integration.o: integration.c integration.h
	gcc  $(FLAGS) -c integration.c  -lm 

	
	
	
clean:
	rm -rf *.o 
