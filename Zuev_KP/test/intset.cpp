#include <string>
#include "intset.h"
#include <iostream>

IntSet::IntSet(int a, int b)
{
	a_ = a;
	b_ = b;
	elements_ = new int[b-a+1];
	size_ = b-a+1;
	for(int k = 0; k < size_; k++)
		elements_[k] = b_+1;
	n_ = 0;
}

IntSet::IntSet(const IntSet & right)
{
	elements_ = new int[size_ = right.size_];
	for(int k = 0; k < size_; k++)
		elements_[k] = right.elements_[k];
	n_ = right.n_;
}

IntSet::~IntSet()
{
	delete[] elements_;
}

void IntSet::put(int item)
{
	if ((item > b_) || (item < a_))
	{
		throw IntSetError(-1, std::string( "нет"));
	}
	for (int k = 0; k < n_; k++)
	{
		if (item == elements_[k])
		{
			return;
		}
	}
	elements_[n_++] = item;
}

void IntSet::exc(int item)
{
	if ((item > b_) || (item < a_))
		throw IntSetError(-5, std::string( "нет"));
	for(int k = 0; k < n_; k++)
		if (item == elements_[k])
		{
			for(int i = k; i < n_-1; i++)
				elements_[i] = elements_[i+1];
			elements_[n_-1] = 0;
		}
	n_ = n_-1;
}

int IntSet::lima()
{
	int left = a_;
	return left;	
}

int IntSet::limb()
{
	int right = b_;
	return right;
}

int IntSet::max()
{
	if(is_empty())
		throw IntSetError(-5, std::string("пусто"));
	int max = elements_[0];
	for(int k = 0; k < n_; k++)
	{
		if(max <= elements_[k])
			max = elements_[k];
	}
	return max;
}

int IntSet::min()
{
	if(is_empty())
		throw IntSetError(-5, std::string("пусто"));
	int min = elements_[0];
	for(int k = 0; k < n_; k++)
	{
		if(min >= elements_[k])
			min = elements_[k];
	}
	return min;
}

IntSet & IntSet::operator=(const IntSet & right)
{
	if(this == &right)
	{
		return *this;
	}
	delete[] elements_;
	elements_ = new int[size_ = right.size_];
	for(int k = 0; k < size_; k++)
		elements_[k] = right.elements_[k];
	n_ = right.n_;
	return *this;
}

void operator*= (IntSet &lev, const IntSet& prav)
{
	IntSet res(lev.a_, lev.b_);
	res = lev*prav;
	lev = res;
}

IntSet operator* (const IntSet &lev, const IntSet& prav)
{
	if(&lev == &prav)
	{
		return lev;
	}

	int a1 = prav.a_;
	int b1 = prav.b_;
	if(lev.a_ >= a1)
		a1 = lev.a_;
	if(lev.b_ <= b1)
		b1 = lev.b_;
	IntSet res(a1, b1);
	for(int k = a1; k <= b1; k ++)
	{
		if((lev.find(k) + prav.find(k)) == 2)
			res.put(k);

	}
	return res;
}

bool operator== (const IntSet& lev, const IntSet& prav)
{
	if(&lev == &prav)
	{
		return true;
	}

	for(int k = 0; k < lev.n_; k ++)
	{
		if((prav.find(lev.elements_[k])) != 1)
			return false;
	}
	for(int k = 0; k < prav.n_; k ++)
	{
		if((lev.find(prav.elements_[k])) != 1)
			return false;
	}
	return true;
}

std::ostream & operator<<(std::ostream &os, const IntSet &q)
{
	os << "IntSet of size " << q.n_ << " with " << q.n_ << " items:\n";
	for(int k = 0; k < q.n_; k++)
	{
		os << "\t" << q.elements_[k] << "\n";
	}
	return os;
}
