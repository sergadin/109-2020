

FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: main.o  find_root.o integration.o solve11.o  ../lib/exmath.o
	gcc $(FLAGS) main.o find_root.o integration.o solve11.o ../lib/exmath.o -o prog  -lm
main.o: main.c
	gcc $(FLAGS) -c main.c -lm
find_root.o: find_root.c find_root.h
	gcc $(FLAGS) -c find_root.c -o find_root.o -lm
integration.o: integration.h integration.c
	gcc $(FLAGS) -c integration.c -o integration.o -lm
solve11.o: solve11.h solve11.c
	gcc $(FLAGS) -c solve11.c -o solve11.o -lm

../lib/exmath.o: ../lib/exmath.c ../lib/exmath.h
	gcc $(FLAGS) -c ../lib/exmath.c -o ../lib/exmath.o
