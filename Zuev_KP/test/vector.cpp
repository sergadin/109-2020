#include <string>
#include "vector.h"
#include <iostream>

Vector::Vector(int n, int k)
{
	a_ = a;
	b_ = b;
	elements_ = new int[b-a+1];
	size_ = b-a+1;
	for(int k = 0; k < size_; k++)
		elements_[k] = b_+1;
	n_ = 0;
}

Vector::Vector(const Vector & right)
{
	elements_ = new int[size_ = right.size_];
	for(int k = 0; k < size_; k++)
		elements_[k] = right.elements_[k];
	n_ = right.n_;
}

Vector::~Vector()
{
	delete[] elements_;
}

