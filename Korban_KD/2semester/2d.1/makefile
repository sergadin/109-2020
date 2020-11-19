

FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: main.o matr.o rank.o ../lib/exmath.o
	gcc $(FLAGS) main.o matr.o rank.o -o prog ../lib/exmath.o -lm
main.o: main.c
	gcc $(FLAGS) -c main.c -lm
rank.o: rank.c rank.h
	gcc $(FLAGS) -c rank.c  -lm
matr.o: matr.c matr.h
	gcc $(FLAGS) -c matr.c -o matr.o -lm

../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o
