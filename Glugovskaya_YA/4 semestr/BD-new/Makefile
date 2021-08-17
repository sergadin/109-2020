a.exe:  ListOD.o test.o Matrix.o DataBase.o
	g++ ListOD.o Matrix.o DataBase.o test.o
LosiOD.o: S.h ListOD.cpp
	g++ -c ListOD.cpp
Matrix.o: S.h Matrix.cpp
	g++ -c Matrix.cpp
DataBase.o: S.h DataBase.cpp
	g++ -c DataBase.cpp	
test.o: S.h test.cpp
	g++ -c test.cpp