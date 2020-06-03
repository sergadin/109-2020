

FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: main.o matr.o solve55.o
	gcc $(FLAGS) main.o matr.o solve55.o -o prog -lm
main.o: main.c
	gcc $(FLAGS) -c main.c -lm
solve55.o: solve55.c solve55.h
	gcc $(FLAGS) -c solve55.c -o solve55.o -lm
matr.o: matr.c matr.h
	gcc $(FLAGS) -c matr.c -o matr.o -lm
