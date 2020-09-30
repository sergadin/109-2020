COMPILE = -O3
prog.exe: main.o min.o
	gcc main.o min.o -o prog.exe
main.o: main.c min.h
	gcc -c $(COMPILE) main.c
min.o: min.c min.h
	gcc -c $(COMPILE) min.c
clean:
	rm -f *.o *.exe *.out
