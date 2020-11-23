&(FLAGS)  = -fsanitize=address -Wall
a.out:  list_arr.o main.o
	g++ $(FLAGS) list_arr.o main.o -o a.out 
list_arr.o: list_arr.cpp list_arr.h
	g++ $(FLAGS) -c list_arr.cpp
main.o: main.cpp list_arr.h
	g++ $(FLAGS) -c main.cpp
	

