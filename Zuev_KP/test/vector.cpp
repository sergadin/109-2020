#include <string>
#include "vector.h"
#include <iostream>

Vector::Vector(int n, int k)
{
	if ((k<0) && (k>n-1))
	{
		throw VectorError(-5, std::string( "нет"));
	}
	n_ = n;
	k_ = k;
	elements_ = new int[n_];
	for(int k = 0; k < n_; k++)
		elements_[k] = 0;
}

Vector::~Vector()
{
	delete[] elements_;
}

void Vector::loc()
{
	 elements_[k_] = elements_[k_]+1;
}

void Vector::rec(const Vector& lev, const Vector& prav)
{
	if(lev.n_ != prav.n_)
        {
                throw VectorError(-1, std::string( "нет"));
        }
	int i = prav.k_;
	lev.elements_[i] = prav.elements_[i];
}

bool operator<= (const Vector& lev, const Vector& prav)
{
        if(&lev == &prav)
        {
                return true;
	}
	if(lev.n_ != prav.n_)
        {
		throw VectorError(-4, std::string( "нет"));
        }
        for(int i = 0; i < lev.n_; i ++)
        {
                if(lev.elements_[i] > prav.elements_[i])
			return false;
        }
	return true;
}

Vector & Vector::operator=(const Vector & right)
{
        if(this == &right)
        {
                return *this;
        }
        delete[] elements_;
        elements_ = new int[n_ = right.n_];
	n_ = right.n_;
	k_ = right.k_;
	for(int i = 0; i < n_; i++)
		elements_[i] = right.elements_[i];
	return *this;
}


std::ostream & operator<<(std::ostream &os, const Vector& q)
{
	os << "sobytiye " << q.k_ << " items:\n";
	for(int k = 0; k < q.n_; k++)
	{
		os << "\t" << q.elements_[k] << "\n";
	}
	return os;
}
