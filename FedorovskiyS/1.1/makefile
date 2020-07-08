COMPILE = -O3
prog.exe: main.o root.o
	gcc main.o root.o -o prog.exe
main.o: main.c root.h
	gcc -c $(COMPILE) main.c
root.o: root.c root.h
	gcc -c $(COMPILE) root.c
clean:
	rm -f *.o *.exe *.out
