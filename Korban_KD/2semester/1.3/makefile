FLAGS = -W -Wall -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -fstack-protector-all -Wfloat-equal -Wpointer-arith -Wwrite-strings -Wcast-align -Wno-long-long -Wmissing-declarations

prog: ../lib/exmath.o test.o find_root.o 
	gcc $(FLAGS) test.o ../lib/exmath.o find_root.o -o prog -lm
../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc  $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o -lm
test.o: test.c
	gcc $(FLAGS) -c test.c -lm
find_root.o: find_root.c find_root.h
	gcc $(FLAGS) -c find_root.c -lm

	
	
	
clean:
	rm -rf *.o 
