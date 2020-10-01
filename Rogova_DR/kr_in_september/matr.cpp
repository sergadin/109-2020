#include <string>
#include "matr.h"
#include <iostream>

Matr::Matr(int left, int right)
{
	if(left >= right)
	{
		throw MatrError(-1, std::string("Null size of..."));
	}
	elements_ = new int[right - left + 1];
	for(int k = 0; k < right - left + 1; k++)
	{
		elements_[k] = right + 1;
	}
	size_ = 0;
	left_ = left;
	right_ = right;
}


Matr::~Matr() 
{
	delete[] elements_;
}

Matr::Matr(const Matr & prav)
{
	elements_ = new int[prav.right_ - prav.left_ + 1];
	size_ = prav.size_;
	right_ = prav.right_;
	left_ = prav.left_;
	for(int k = 0; k < right_ - left_ + 1; k ++)
	{
		elements_[k] = prav.elements_[k];
	}

}
void Matr::put(int el)
{
	int ind = 0;
	if((el < left_) || (el > right_))
	{
		throw MatrError(-2, std::string("No place"));
	}
	for(int k = 0; k < right_ - left_ + 1; k ++)
	{
		if(el == elements_[k])
			ind = 1;
	}
	if(ind == 0)
	{
		size_ ++;
		elements_[size_ - 1] = el;
	}
		
}

int Matr::minn()
{
	int mini = right_ + 1;
	if(size_ <= 0)
	{
		return (left_ - 1);
	}
	for(int k = 0; k < size_; k ++)
	{
		if(elements_[k] < mini)
		{
			mini = elements_[k];
		}
	}
	return mini;
}

int Matr::maxx()
{
        int maxi = left_ - 1;
        if(size_ <= 0)
        {
                return (right_ + 1);
        }
        for(int k = 0; k < size_; k ++)
        {
                if(elements_[k] > maxi)
                {
                        maxi = elements_[k];
                }
        }
        return maxi;
}

void Matr::del_elem(int el)
{
	if(size_ <= 0)
	{
		throw MatrError(-1, std::string("Null size of..."));
	}

	int ind = 0;
	int place;
	for(int k = 0; k < size_; k ++)
	{
		if(el == elements_[k])
		{
			ind = 1;
			place = k;
		}
	}
	if(ind == 1)
	{
		for(int k = place + 1; k < left_ - right_ + 1; k ++)
		{
			elements_[k - 1] = elements_[k];
		}

	}
	size_ --;
}
int Matr::find_size()
{
	return size_;
}
Matr & Matr::operator=(const Matr & prav)
{
	if(this == &prav)
	{
		return *this;
	}
	delete[] elements_;
	elements_ = new int[prav.right_ - prav.left_ + 1];
	right_ = prav.right_;
	left_ = prav.left_;
	size_ = prav.size_;
	for(int k = 0; k < size_; k++)
		elements_[k] = prav.elements_[k];
	for(int j = size_; j < right_ - left_ + 1; j ++)
	{
		elements_[j] = right_ + 1;
	}

	return *this;
}
Matr operator* (const Matr& lev, const Matr& prav)
{
	if(&lev == &prav)
        {
                return lev;
        }

	int legr = prav.left_;
	int pragr = prav.right_;
	if(lev.left_ >= legr)
		legr = lev.left_;
	if(lev.right_ <= pragr)
		pragr = lev.right_;
	Matr res(legr, pragr);
	for(int k = legr; k <= pragr; k ++)
	{
		if((lev.find_el(k) + prav.find_el(k)) == 2)
			res.put(k);

	}
	return res;
}
bool operator== (const Matr& lev, const Matr& prav)
{
	if(&lev == &prav)
        {
                return true;
        }

	for(int k = 0; k < lev.size_; k ++)
	{
		if((prav.find_el(lev.elements_[k])) != 1)
			return false;
	}
	for(int k = 0; k < prav.size_; k ++)
        {
                if((lev.find_el(prav.elements_[k])) != 1)
                        return false;
        }
	return true;

}


std::ostream & operator<<(std::ostream &os, const Matr &q)
{
	os << "Matr of size" << q.size_  << "items:\n";
	for(int k = 0; k < q.size_; k ++)
	{
		os << "\t" << q.elements_[k] << "\n";
	}
	return os;

}


