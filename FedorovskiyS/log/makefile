COMPILE = -O3
prog.exe: main.o ln.o
	gcc main.o ln.o -o prog.exe
main.o: main.c ln.h
	gcc -c $(COMPILE) main.c
ln.o: ln.c ln.h
	gcc -c $(COMPILE) ln.c
clean:
	rm -f *.o *.exe *.out
