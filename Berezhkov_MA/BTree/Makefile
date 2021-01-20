CXX := clang++
CXXFLAGS := -std=c++20 -pedantic -Wall -Wextra -Werror -g -fsanitize=address -fsanitize=undefined

all: main main_test

test: main_test
	@./main_test

clean:
	@rm -f main main_test main.o keyval.o parser.o main_test.o testing.o

main: main.o parser.o keyval.o
	${CXX} ${CXXFLAGS} -O3 -flto -o main main.o parser.o keyval.o

main.o: main.cxx parser.hxx keyval.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o main.o main.cxx

main_test: main_test.o testing.o parser.o keyval.o
	${CXX} ${CXXFLAGS} -O3 -flto -o main_test main_test.o testing.o parser.o keyval.o

main_test.o: main_test.cxx testing.hxx btree.hxx keyval.hxx parser.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o main_test.o main_test.cxx

parser.o: parser.cxx parser.hxx keyval.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o parser.o parser.cxx

keyval.o: keyval.cxx keyval.hxx btree.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o keyval.o keyval.cxx

testing.o: testing.cxx testing.hxx
	${CXX} ${CXXFLAGS} -O3 -flto -c -o testing.o testing.cxx

.PHONY: all run test clean
