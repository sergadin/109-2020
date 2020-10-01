#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
#include "intset.hpp"


/*
class inte{
	private:
		int n;
		int left;
		int right;
		int *a;
	public:
		inte(int left, int right);//+
		~inte();//+
		inte(const inte &integer); //конструктор копирования
		inte& operator=(const inte &integer); //оператор присваивания
		inte& operator==(const inte &integer);
		int check() const; //+проверка пустоты множества
		int fmin() const;//+
		int fmax() const;//+
		int fleft() const;//+
		int fright() const;//+
		void print() const;
		void add(int x);//+
		void del(int x);//+
        
        friend inte& operator*(const inte &x, const inte &y);
        friend inte& operator*=(inte &x, const inte &y);
};

*/


inte::inte(int l, int r) {
	n = 0;
	left = l;
	right = r;
}

inte::~inte() {
	if(n != 0)
		free(a);
	left = 0;
	right = 0;
	n = 0;
}

int inte::fleft() const{
	return left;
}

int inte::fright() const{
	return right;
}

int inte::fmax() const{
	int max = left;
	if (n == 0)
		std::cout << "пустое множество";
	for (int i = 0; i < n; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

int inte::fmin() const{
	int min = left;
	if (n == 0)
		std::cout << "пустое множество";
	for (int i = 0; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

int inte::check() const {
	if(n == 0)
		return 1;
	return 0;
}

void inte::add(int x) {
	if(x >= left && x <= right) {
		int f = 1;
		for(int i = 0; i < n; i++) {
	        if(x == a[i])
                f = 0;
		}
        if(f == 1) {
            n++;
            a = (int *)realloc(a, n * sizeof(int));
            a[n - 1] = x;
        }
	}
}

void inte::del(int x) {
	if(x >= left && x <= right) {
		int f = 1, q;
		for(int i = 0; i < n; i++) {
	        if(x == a[i]) {
                f = 0;
                q = i;
                break;
            }
		}
        if(f == 0) {
            a[q] = a[n - 1];
            n--;
            a = (int *)realloc(a, n * sizeof(int));
        }
	}
}

inte& operator*=(inte &x, const inte &y) {
    return x;
}
