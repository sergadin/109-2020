#include "matrix.h"

matrix::matrix(int n, int m)
{
	if ((n<=0)||(m<=0))
	{
		throw Exception(2, "Invalid inputs");
	}
	if( !(elements_ = new double[n*m]))
	{
		throw Exception(1, "Memory allocation error");
	}
	
	n_ = n;
	m_ = m;
	for(int i=0; i<n*m; ++i)
	{
		elements_[i] = 0;
	}
}

matrix::~matrix()
{
	n_ = 0;
	m_ = 0;
	delete[] elements_;
}

matrix& matrix::operator=(const matrix &other)
{
	
	this->n_ = other.n_;
	this->m_ = other.m_;
	delete[] elements_;
	if(!(this->elements_ = new double[n_*m_]))
	{
		throw Exception(1, "Memory allocation error");
	}
	for(int i=0; i<n_*m_; ++i)
	{
		this->elements_[i] = other.elements_[i];	
	}
	return *this;
}

int matrix::get_rows() const
{
	return this->n_;
}

int matrix::get_cols() const
{
	return this->m_;
}

double matrix::get_elem(int i, int j) const
{
	if((i>n_)||(j>m_)||(i<1)||(j<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	return this->elements_[(i-1)*m_+j-1];
}

void matrix::set_elem(double val, int i, int j)
{
	if((i>n_)||(j>m_)||(i<1)||(j<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	this->elements_[(i-1)*m_+j-1] = val;
}

matrix matrix::operator+(const matrix &right)
{
	if ((this->n_!=right.n_)||(this->m_!=right.m_))
	{
		throw Exception(4, "Matrices have different sizes");
	}
	matrix buffer(1,1);
	buffer = *this;
	for(int i = 0; i<n_*m_; ++i)
	{
		buffer.elements_[i]+=right.elements_[i];
	}
	return buffer; 
}

std::ostream& operator<<(std::ostream &os, const matrix& matr)
{
	os << "size: " << matr.n_ << "*" << matr.m_ << endl;
	os << "matrix:" << endl;
	for(int i=0; i<matr.n_*matr.m_; ++i)
	{
		os << matr.elements_[i] << " ";
		if (i%matr.m_ == matr.m_-1)
		{
			os << endl;
		}
	}
	os << endl; 
	return os;
}

submatrix::submatrix(matrix *matr,int i,int j,int n,int m)
{
	if((i>matr->get_rows())||(j>matr->get_cols())||(i<1)||(j<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	if ((n+i>matr->get_rows())||(m+j>matr->get_cols())||(n<1)||(m<1))
	{
		throw Exception(5, "Incorrect submatrix size input");
	}
	i_=i;
	j_=j;
	N_=n;
	M_=m;
	matr_=matr;
}

submatrix::~submatrix()
{
	i_ = 0;
	j_ = 0;
	N_ = 0;
	M_ = 0;
}

double submatrix::get_elem(int n, int m) const
{
	if((n>N_)||(m>M_)||(n<1)||(m<1))
	{
		throw Exception(3, "Incorrect element index");
	}
	
	return matr_->get_elem(i_+n-1, j_+m-1);
}


