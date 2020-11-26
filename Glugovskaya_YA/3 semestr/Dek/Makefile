a.exe: test.o Dek.o
	g++ test.o Dek.o
Dek.o: Dek.h Dek.cpp
	g++ -c Dek.cpp
test.o: Dek.h test.cpp 
	g++ -c test.cpp