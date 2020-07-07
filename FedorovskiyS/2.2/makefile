COMPILE = -O3
prog.exe: main.o INT.o
	gcc main.o INT.o -o prog.exe
main.o: main.c INT.h
	gcc -c $(COMPILE) main.c
task.o: INT.h INT.h
	gcc -c $(COMPILE) INT.c
clean:
	rm -f *.o *.exe *.out
