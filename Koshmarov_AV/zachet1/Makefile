all : do_it clean

main.o : main.c help.h
	gcc -c main.c

get_string.o : get_string.o help.h
	gcc -c get_string.c

delete_char.o : delete_char.o help.h
	gcc -c delete_char.c

coup_string.o : coup_string.o help.h
	gcc -c coup_string.c

a.out : main.o get_string.o delete_char.o coup_string.o
	gcc main.o get_string.o delete_char.o coup_string.0

do_it : a.out
	./a.out

clean : main.o get_string.o
	rm main.o get_string.o delete_char.o coup_string.o a.out
