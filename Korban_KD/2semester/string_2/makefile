FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: test.o replace.o ../lib/exstring.o 
	gcc  $(FLAGS) -o prog -Wall test.o replace.o exstring.o  -lm 
test.o: test.c replace.h
	gcc $(FLAGS)  -c test.c -lm 
replace.o: replace.c replace.h
	gcc $(FLAGS)  -c replace.c -lm 
../lib/exstring.o: ../lib/exstring.h ../lib/exstring.c
	gcc $(FLAGS) -c ../lib/exstring.c

clean:
	rm -rf *.o 
