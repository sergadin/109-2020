all: main

clean:
	rm -rf *.o

main: main.o db.o
	g++ -Wall -std=c++17 -O2 -Werror main.o db.o -o main

db.o: db.h db.cpp
	g++ -c -Wall -std=c++17 -O2 -Werror db.cpp -o db.o

main.o: main.cpp
	g++ -c -Wall -std=c++17 -O2 -Werror main.cpp -o main.o
