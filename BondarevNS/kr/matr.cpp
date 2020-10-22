#include "matr.h"

matr::matr(int n, int m)
{
		if ((n<=0)||(m<=0))
	{
		throw Exception(2, "Invalid inputs");
	}
	if( !(array_ = new double[n*m]))
	{
		throw Exception(1, "Memory allocation error");
	}
	
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
		if(!(this->array_ = new double[n_*m_]))
	{
		throw Exception(1, "Memory allocation error");
	}
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
	
   if((i>n_)||(j>m_)||(i<1)||(j<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	return array_[(i-1)*m_+j-1];
  	
} 

matr& matr::operator+(const matr &right)
{
	if ((this->n_!=right.n_)||(this->m_!=right.m_))
	{
		throw Exception(4, "Matrices have different sizes");
	}
	matr res_matr(1,1);
	res_matr = *this;
	for(int i = 0; i<n_*m_; i++)
	{
		res_matr.array_[i]+=right.array_[i];
	}
	return res_matr; 
}

void matr::set_element(double C, int i, int j)
{
	if((i>n_)||(j>m_)||(i<1)||(j<1))
	{
		throw Exception(3, "Incorrect element index");
	}
		array_[(i-1)*m_+j-1] = C;
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


podmatr::podmatr(matr *pod_,int i_, int j_,int n_,int m_)
{
	if((i_>pod->get_height())||(j_>pod->get_length())||(i_<1)||(j_<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	if ((n_+i_>pod->get_height())||(m_+j_>pod->get_length())||(n_<1)||(m_<1))
	{
		throw Exception(5, "Incorrect submatrix size input");
	}
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

double podmatr::get_element(int n, int m) const
{
	if((n>n_)||(m>m_)||(n<1)||(m<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	return pod ->get_element(i+n-1, j+m-1);
}
