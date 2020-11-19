#include "class.h"

matrix::matrix(int N, int M)
{
	if ((N<1)||(M<1))
	{
		throw iskl(1, "ERROR size of matrix");
	}
	if(!(array_ = new double[N*M]))
	{
		throw iskl(2, "ERROR memory");
	}
	 
	N_=N;
	M_=M;
	for (int i=0; i < N*M; i++)
	{
		array_[i] = 1;
	}
}


matrix::~matrix()
{
	N_ = 0;
	M_ = 0;

	delete[] array_;
}

matrix& matrix::operator=(const matrix &other)
{
	this->N_ = other.N_;
	this->M_ = other.M_;
	
	delete[] array_;
	
	if(!(this->array_ = new double[N_*M_]))
	{
		throw iskl(2, "ERROR memory");
	}

	for(int i=0; i<N_*M_; ++i)
	{
		this->array_[i] = other.array_[i];
	}
	return *this;
}


int matrix::str() const
{
        return this->N_;
}

int matrix::stolb() const
{
        return this->M_;
}

double matrix::element(int i, int j) const
{

        if((i<1)||(j<1)||(i>N_)||(j>M_))
	{
		throw iskl(3, "ERROR index");
	}
	return array_[j+(i-1)*M_-1];

}


matrix matrix::operator+(const matrix &right)
{
	if ((this->N_!=right.N_)||(this->M_!=right.M_))
	{
		throw iskl(4, "ERROR sum");
	}

	matrix outmatrix(1,1);
	outmatrix = *this;
	
	for (int i = 0; i < N_*M_; i++)
	{
		outmatrix.array_[i] += right.array_[i];
	}
	return outmatrix;
}

void matrix::change(double t, int i, int j)
{
	if((i<1)||(j<1)||(i>N_)||(j>M_))
	{
		throw iskl(3, "ERROR index");
	}

	array_[j+(i-1)*M_-1] = t;
}

std::ostream& operator<<(std::ostream &os, const matrix& q)
{
	os<<"size of matrix is "<<q.N_<<"*"<<q.M_<<endl;

	for(int i = 0; i < q.N_*q.M_; i++)
	{
		os<<q.array_[i]<<" ";

		if(i%q.M_==q.M_-1)
		{
			os<<endl;
		}
	}

	return os;
}


podmatrix::podmatrix(matrix *podmatr_, int i_, int j_, int n, int m)
{
	if ((i_>podmatr_->str())||(j_>podmatr_->stolb())||(i_<1)||(j_<1))
	{
		throw iskl(3, "ERROR index");
	}
	if ((n+i_-1>podmatr_->str())||(m+j_-1>podmatr_->stolb())||(n<1)||(m<1))
	{
		throw iskl(5, "ERROR podmatrix");
	}

	i=i_;
	j=j_;
	podN=n;
	podM=m;
	podmatr=podmatr_;
}

podmatrix::~podmatrix()
{
	i=0;
	j=0;
	podN=0;
	podM=0;
}

double podmatrix::element(int n, int m) const
{
	if((n>podN)||(m>podM)||(n<1)||(m<1))
	{
		throw iskl(3, "ERROR index");
	}
	return podmatr->element(i+n-1, j+m-1);
}
