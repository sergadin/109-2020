all : do_it clean

main.o : main.c help.h
	gcc -c main.c

read_string.o : read_string.o help.h
	gcc -c read_string.c

a.out : main.o read_string.o
	gcc main.o read_string.o

do_it : a.out
	./a.out

clean : main.o read_string.o
	rm main.o read_string.o a.out
