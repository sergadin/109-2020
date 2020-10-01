#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

class queue {
    private:
        int n;
        int size;
        double *array;
        
    public:
        queue();
        queue(int new_size);
        queue operator +(const queue &other);
        void print() const;
        int checkVoid() const;
        int checkfull() const;
        int CheckSize() const;
        void resize(int new_size);
        void push(double n);
        double pop();
        void clean();
        ~queue();
};


class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};
