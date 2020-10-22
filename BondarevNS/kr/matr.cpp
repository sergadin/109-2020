#include "matr.h"

matr::matr(int n, int m)
{
	array_ = new double[n*m];
	n_ = n;
	m_ = m;
	for(int i=0; i<n*m; i++)
		{
			array_[i] = 0;
		}
}

matr::~matr()
{
	n_ = 0;
	m_ = 0;
	delete[] array_;
}

matr& matr::operator=(const matr &other)
{

	this->n_ = other.n_;
	this->m_ = other.m_;
	delete[] array_;
	this->array_ = new double[n_*m_];
	for(int i=0; i<n_*m_; ++i)
	{
		this->array_[i] = other.array_[i];
	}
}

int matr::get_height() const
{
return n_;
}

int matr::get_length() const
{
return m_;
}

double matr::get_element(int i, int j) const
{
	
    if ((m_ > 0) && (n_ > 0))
      return array_[i*m_ + j];
    else
      return 0;
  	
} 

matr& matr::operator+(const matr &right)
{
	matr res_matr(1,1);
	res_matr = *this;
	for(int i = 0, i<n_*m_, i++)
	{
		res_matr.array_[i]+=right.array_[i];
	}
	return res_matr; 
}

void matr::set_element(double C, int i, int j)
{
	this->array_[(i-1)*m_+j-1] = C;
}


std::ostream& operator<<(std::ostream &os, const matr& Q)
{
	os << "size: " <<Q.n_<< "*" << Q.m_ << endl;
	for(int i=0; i<Q.n_*Q.m_; i++)
	{
		os <<Q.array_[i]<<" ";
		if(i%Q.m_ == Q.m_ - 1)
		{
			os << endl;
		}
	}
	return os;	
}


podmatr::podmatr(matr *pod, i, j, n, m)
{
	i=i_;
	j=j_;
	n1=n_;
	m1=m_;
	pod=pod_;
}

podmatr::~podmatr()
{
	i = 0;
	j = 0;
	n1 = 0;
	m1 = 0;
}

double podmatr::get_element(int n_, int m_) const
{
	return pod ->get_element(i+n_-1, j+m_-1);
}
