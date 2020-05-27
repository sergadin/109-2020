FLAGS =-fsanitize=address -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -std=gnu99 -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wold-style-definition -Wdeclaration-after-statement -Wbad-function-cast -Wnested-externs



prog: test.o sort_files_by_size.o 
	gcc  $(FLAGS) -o prog  test.o sort_files_by_size.o 
test.o: test.c sort_files_by_size.h
	gcc $(FLAGS)  -c test.c 
sort_files_by_size.o:  sort_files_by_size.h sort_files_by_size.c
	gcc $(FLAGS)  -c sort_files_by_size.c 
clean:
	rm -rf *.o 
