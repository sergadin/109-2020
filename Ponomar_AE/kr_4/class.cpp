#include "class.h"

matrix::matrix(int N, int M)
{
	array_ = new double[N*M];

	for (int i=0; i < N_*M_; i++)
	{
		array_[i] = 0;
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

	this->array_ = new double[N_*M_];

	for(int i=0; i < N_*M_; i++)
	{
		this->array_[i] = other.array_[i];
	}
	return *this;
}


int matrix::str()
{
        return this->N_;
}

int matrix::stolb()
{
        return this->M_;
}

double matrix::element(int i, int j)
{

	if ((N_>0)&&(M_>0))
	{
		return array_[j+(i-1)*M_-1];
	}

	else
	{
		return 0;
	}
}

void matrix::change(int i, int j, double t)
{
       	this->array_[i*M_+j] = t;
}


matrix matrix::operator+(const matrix &right)
{
	matrix outmatrix(1,1);
	outmatrix = *this;
	
	for (int i = 0; i < N_*M_; i++)
	{
		outmatrix.array_[i] += right.array_[i];
	}
	return outmatrix;
}


std::ostream& operator<<(std::ostream&os, const matrix&q)
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


podmatrix::podmatrix(matrix *podmatr_, int i_, int j_, int N_, int M_)
{
	i=i_;
	j=j_;
	podN=N_;
	podM=M_;
	podmatr=podmatr_;
}

podmatrix::~podmatrix()
{
	i=0;
	j=0;
	podN=0;
	podM=0;
}


double podmatrix::element(int N_, int M_)
{
	return podmatr->element(i+N_-1, j+M_-1);
}
