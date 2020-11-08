#include "iterator.h"

IntArray::IntArray(int n)
{
	if (n<=0)
	{
		throw Exception(1, "Invalid input");
	}
	n_ = n;
	if(!(arr_ = new int[n_]))
	{
		throw Exception(2, "Memory allocation error");
	}
	for (int i = 0; i< n_; i++)
		{
			arr_[i] = 0;
		}
}

IntArray::~IntArray()
{
	n_=0;
	delete[] arr_;
} 

IntArray::IntArray(const IntArray &other)
{
	int nsize = n_;
	arr_ = new int[nsize = other.n_];
	for (int k = 0; k < nsize; k++) 
	{
		arr_[k] = other.arr_[k];
	}
	n_ = other.n_;
}

int IntArray::get_elem(int i) const
{
	if((i<=0)||(i>n_))
	{
		throw Exception(3, "Incorrect element index");
	}
	return this->arr_[i-1];
}

void IntArray::set_elem(int i, int cmp)
{
	if((i<=0)||(i>n_))
	{
		throw Exception(3, "Incorrect element index");
	}
	this->arr_[i-1] = cmp;
}

void IntArray::del_elem(int i)
{
	if((i<=0)||(i>n_))
	{
		throw Exception(3, "Incorrect element index");
	}
	for (int j=i; j<n_; j++)
	{
		arr_[j-1] = arr_[j];
	}
	arr_[n_-1] = 0;
}

int IntArray::find_elem(int cmp) const
{
	for (int i = 0; i<n_; i++)
	{
		if (arr_[i] == cmp);
		return i;
	}
	return -1;
}

IntArray& IntArray::operator=(const IntArray &other)
{
	this->n_ = other.n_;	
	delete[] arr_;
	if(!(this->arr_ = new int[n_]))
	{
		throw Exception(1, "Memory allocation error");
	}
	for(int i=0; i<n_; i++)
	{
		this->arr_[i] = other.arr_[i];	
	}
	return *this;
}

iterator_1 IntArray::begin()
{
	iterator_1 a(0, this); 
	return a;
}

std::ostream& operator<<(std::ostream &os, const IntArray& array)
{
	os << "size: " << array.n_ << endl; 
	for(int i=0; i<array.n_; i++)
	{
		os << array.arr_[i] << " ";
	}
	os << endl; 
	return os;
}

iterator_1::iterator_1(int pos, IntArray *array)
{
	if((pos<0)||(pos>=array->n_))
	{
		throw Exception(4, "incorrect position");
	}
	pos_ = pos;
	array_ = array;
}

iterator_1::~iterator_1()
{
	pos_ = 0;
}

bool iterator_1::check_bound()
{
	if (pos_==array_->n_){
	return false;
	}
	return true;
}

int iterator_1::get_cmp()
{
	return array_->arr_[pos_];
}

void iterator_1::step()
{
	pos_=pos_ + 1;
}

iterator_1& iterator_1::operator=(const iterator_1 &other)
{
	this->pos_ = other.pos_;
	this->array_ = other.array_;	
	return *this;
}

