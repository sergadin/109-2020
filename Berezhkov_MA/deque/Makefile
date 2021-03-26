CXX := clang++
CXXFLAGS := -std=c++20 -pedantic -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

main_test: main_test.o testing.o
	${CXX} ${CXXFLAGS} -O3 -flto -o main_test main_test.o testing.o

main_test.o: main_test.cxx testing.hxx deque.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o main_test.o main_test.cxx

testing.o: testing.cxx testing.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o testing.o testing.cxx

test: main_test
	@./main_test

clean:
	@rm -f main_test main_test.o testing.o

.PHONY: test clean
