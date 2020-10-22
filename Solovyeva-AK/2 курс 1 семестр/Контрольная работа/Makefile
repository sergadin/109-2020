CPPFLAGS = -fsanitize=address -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -std=c++11
a.exe: test.o Time.o
	g++ $(CPPFLAGS) test.o Time.o
Time.o: Time.cpp Time.h
	g++ -c $(CPPFLAGS) Time.cpp
test.o: test.cpp 
	g++ -c $(CPPFLAGS) test.cpp