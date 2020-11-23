FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: test.o sort_words_file.o 
	gcc  $(FLAGS) -o prog  test.o sort_words_file.o 
test.o: test.c sort_words_file.h
	gcc $(FLAGS)  -c test.c 
sort_words_file.o:  sort_words_file.h sort_words_file.c
	gcc $(FLAGS)  -c sort_words_file.c 
clean:
	rm -rf *.o 
