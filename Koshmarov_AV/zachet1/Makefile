all : do_it clean

main.o : main.c help.h
	gcc -c main.c

get_string.o : get_string.c help.h
	gcc -c get_string.c

delete_char.o : delete_char.c help.h
	gcc -c delete_char.c

coup_string.o : coup_string.c help.h
	gcc -c coup_string.c

func.o : func.c help.h
	gcc -c func.c

a.out : main.o get_string.o delete_char.o coup_string.o func.o
	gcc main.o get_string.o delete_char.o coup_string.o func.o

do_it : a.out
	./a.out

clean : main.o get_string.o delete_char.o coup_string.o func.o a.out
	rm main.o get_string.o delete_char.o coup_string.o func.o a.out
