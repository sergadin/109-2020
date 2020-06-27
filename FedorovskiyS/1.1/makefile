COMPILE = -O3
prog.exe: main.o task.o
	gcc main.o task.o -o prog.exe
main.o: main.c prot.h
	gcc -c $(COMPILE) main.c
task.o: task.c prot.h
	gcc -c $(COMPILE) task.c
clean:
	rm -f *.o *.exe *.out
