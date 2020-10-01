#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;

class IntSet {
    private:
        int *array_;
        int size_;
        int n_;
        int max_;
        int min_;
        void resize_(int newSize);
        
    public:
        IntSet(int min, int max);
        ~IntSet();
        void operator =(const IntSet &other);
        void add_elem(int new_elem);
        void delete_elem(int d_elem);
        int CheckVoid() const;
        int CheckSize() const;
        int left() const;
        int right() const;
        int CheckMin() const;
        int CheckMax() const;
        void print() const;
        IntSet operator *(const IntSet &other);
        void operator *=(const IntSet &other);
        bool operator ==(const IntSet &other);
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
