#include <string>
#include "stack.h"
#include <iostream>

Stack::Stack(int n, int k)
{
	if ((k<0) || (k>n-1))
	{
		throw StackError(-5, std::string( "нет"));
	}
	elements_ = new int[n];
	for(int i = 0; i < n; i++)
	{
		elements_[i] = 0;
	}
       	n_ = n;
	k_ = k;
}

Stack::~Stack()
{
	delete[] elements_;
}

Stack & Stack::operator=(const Stack & right)
{
        if(this == &right)
        {
                return *this;
        }
        delete[] elements_;
        elements_ = new int[right.n_];
	n_ = right.n_;
	k_ = right.k_;
	for(int i = 0; i < n_; i++)
	{
		elements_[i] = right.elements_[i];
	}
	return *this;
}


std::ostream & operator<<(std::ostream &os, const Stack &q)
{
	os << "sobytiye " << q.k_ << " items:\n";
	for(int i = 0; i < q.n_; i++)
	{
		os << "\t" << q.elements_[i] << "\n";
	}
	return os;
}
