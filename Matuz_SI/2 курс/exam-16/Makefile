WARNINGS_CXX=-fsanitize=address -O3 -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual

CXXFLAGS = $(WARNINGS_CXX) -O2 -fPIC


all:  exam-fun.o exam-test.o 
	g++ $(CXXFLAGS) exam-fun.o exam-test.o

exam-fun.o: exam-fun.cpp exam-test.h 
	g++ -c $(CXXFLAGS) exam-fun.cpp

exam-test.o:  exam-test.cpp exam-test.h 
	g++ -c $(CXXFLAGS) exam-test.cpp

clean:
	rm *.o 
#	del *.o
