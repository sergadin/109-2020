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
	for(int i = 0; i < n_; i++)
		elements_[i] = 0;
}

Vector::~Vector()
{
	delete[] elements_;
}

void Vector::loc()
{
	 elements_[k_] = elements_[k_]+1;
}

void Vector::rec(const Vector& prav)
{
	if(n_ != prav.n_)
        {
                throw VectorError(-1, std::string( "нет"));
        }
	for(int i = 0; i < n_; i ++)
	{
		if(i != k_)
		{
			if(prav.elements_[i] > elements_[i])
			{
				elements_[i] = prav.elements_[i];
			}
		}
		else
		{
			elements_[i] = elements_[i]+1;
		}
	}
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
        elements_ = new int[right.n_];
	n_ = right.n_;
	k_ = right.k_;
	for(int i = 0; i < n_; i++)
		elements_[i] = right.elements_[i];
	return *this;
}


std::ostream & operator<<(std::ostream &os, const Vector& q)
{
	os << "sobytiye " << q.k_ << " items:\n";
	for(int i = 0; i < q.n_; i++)
	{
		os << "\t" << q.elements_[i] << "\n";
	}
	return os;
}
