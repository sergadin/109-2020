FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations

prog: ../lib/exmath.o test.o find_min.o 
	gcc -lm $(FLAGS) test.o ../lib/exmath.o find_min.o -o prog
../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o
test.o: test.c
	gcc $(FLAGS) -c test.c
find_min.o: find_min.c find_min.h
	gcc $(FLAGS) -c find_min.c 	

	
	
	
clean:
	rm -rf *.o 
