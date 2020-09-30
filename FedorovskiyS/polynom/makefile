COMPILE = -O3
prog.exe: main.o polynom.o
	g++ main.o polynom.o -o prog.exe
main.o: main.cpp polynom.h
	g++ -c $(COMPILE) main.cpp
polynom.o: polynom.cpp polynom.h
	g++ -c $(COMPILE) polynom.cpp
clean:
	rm -f *.o *.exe *.out
