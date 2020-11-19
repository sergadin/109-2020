&(FLAGS)  = -fsanitize=address -Wall
a.out:  list_arr.o
	g++ $(FLAGS) list_arr.o -o a.out 
list_arr.o: list_arr.cpp list_arr.h
	g++ $(FLAGS) -c list_arr.cpp

