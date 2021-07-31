FLAGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
FLAGS2 =  -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

test: R2.o test.o
	g++ $(FLAGS) test.o R2.o -o test

client: client.o
	g++ $(FLAGS) client.o  -o client

server:	R2.o server.o
	g++ $(FLAGS) server.o R2.o -o server

server.o: server.cpp 
	g++ $(FLAGS) -c server.cpp 

client.o: client.cpp 
	g++ $(FLAGS) -c client.cpp 


R2.o:R2.cpp 
	g++ $(FLAGS) -c R2.cpp 

test.o: test.cpp 
	g++ $(FLAGS) -c test.cpp 


