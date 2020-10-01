#include <string>
#include "intset.h"

IntSet::IntSet(int a, int b)
{
        a_ = a;
        b_ = b;
        elements_ = new int[b-a+1];
        size_ = b-a+1;
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
                throw IntSetError(-1, std::string( "нет"));
        elements_[n_++] = item;
}

void IntSet::exc(int item)
{
        if ((item > b_) || (item < a_))
                throw IntSetError(-1, std::string( "нет"));
        for(int k = 0; k < n_; k++)
                if elements_[k]= righ[
        n_ = right.n
        elements_[n_++] = item


IntSet & IntSet::operator=(const IntSet & right)

        if(this == &right)
        
                return *this
       
        delete[] elements_
        elements_ = new int[size_ = right.size_]
        for(int k = 0; k < size_; k++)
                elements_[k] = right.elements_[k]
        n_ = right.n_
        return *this


IntSet & operator*=(IntSet &left, const IntSet& right)

        return left


IntSet operator* (const IntSet &left, const IntSet& right)




std::ostream & operator<<(std::ostream &os, const IntSet &q)

        os << "IntSet of size " << q.size_ << " with " << q.n_ << " items:\n"
        for(int k = 0; k < q.n_; k++)
        
                os << "\t" << q.elements_[k] << "\n"
        
        return os


