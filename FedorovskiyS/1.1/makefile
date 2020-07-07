COMPILE = -O3
prog.exe: main.o root.o
	gcc main.o root.o -o prog.exe
main.o: main.c root.h
	gcc -c $(COMPILE) main.c
task.o: task.c root.h
	gcc -c $(COMPILE) task.c
clean:
	rm -f *.o *.exe *.out
