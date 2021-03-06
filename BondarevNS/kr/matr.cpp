#include "matr.h"

matr::matr(int n, int m)
{
		if ((n<=0)||(m<=0))
	{
		throw Exception(2, "������: �������� ����");
	}
	if( !(array_ = new double[n*m]))
	{
		throw Exception(1, "������: ��������� ������");
	}
	

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
		throw Exception(1, "������: ��������� ������");
	}
	for(int i=0; i<n_*m_; ++i)
	{
		this->array_[i] = other.array_[i];
	}
	return *this;
}

int matr::get_height() const
{
	return this->n_;
}

int matr::get_length() const
{
	return this->m_;
}

double matr::get_element(int i, int j) const
{
	
   if((i>n_)||(j>m_)||(i<1)||(j<1))
	{
		throw Exception(3, "������: �������� ������");
	}
	return array_[(i-1)*m_+j-1];
  	
} 

matr matr::operator+(const matr &right)
{
	if ((this->n_!=right.n_)||(this->m_!=right.m_))
	{
		throw Exception(4, "������: ������ �������");
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
		throw Exception(3, "������: �������� ������");
	}
		array_[(i-1)*m_+j-1] = C;
}
matr matr::get_podmatr(int i1, int j1, int n, int m)
{
	matr A(n,m);
    for (int i=1; i<n+1; i++)
    {
        for (int j=1; j<m+1; j++)
        {
            A.set_element(this->get_element(i1+i-1, j1+j-1), i, j);
        }
    }
	return A;
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


podmatr::podmatr(matr *pod_,int i_, int j_,int N,int M)
{
	if((i_>pod_->get_height())||(j_>pod_->get_length())||(i_<1)||(j_<1))
	{
		throw Exception(3, "������: �������� ������");
	}
	if ((N+i_-1>pod_->get_height())||(M+j_-1>pod_->get_length())||(N<1)||(M<1))
	{
		throw Exception(5, "������: �������� ������ ����������");
	}
	i=i_;
	j=j_;
	n1=N;
	m1=M;
	pod=pod_;
}

podmatr::~podmatr()
{
	i = 0;
	j = 0;
	n1 = 0;
	m1 = 0;
}

double podmatr::get_element(int N, int M) const
{
	if((N>n1)||(M>m1)||(N<1)||(M<1))
	{
		throw Exception(3, "������: �������� ������");
	}
	return pod ->get_element(i+N-1, j+M-1);
}
