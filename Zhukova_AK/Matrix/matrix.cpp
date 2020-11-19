#include<iostream>
#include<stdio.h>
#include "matrix.h"

Matrix::Matrix(int l, int k)
{
	int p;
//	int * array;
        n = k;
	m = l;
	p = m*n;

        if (n <= 0 || m <=0)
        {
                throw Exception (1, "Неверные параметры");
        }

        array = (int*)malloc(p*sizeof(*array));

        if (array == NULL)
        {
                throw Exception (2, "Память не выделилась");
        }

        for (int i=0; i<p;i++)
        {
                array[i] = 0;
        }

}

Matrix::Matrix(const Matrix &v)
{
	int p;
        n = v.n;
        m = v.m;
	p = n*m;
        array = (int*)malloc(p*sizeof(*array));

        if (array == NULL)
        {
                throw Exception (2, "Память не выделилась");
        }

        for (int i=0;i<p;i++)
        {
                array[i] = v.array[i];
        }
}

Matrix::~Matrix()
{
        free (array);
}

//Submatrix::~Submatrix()
//{
//        free (array_);
//}

void Matrix::registration (int i, int j, int a)
{
        array[j + (i)*n] = a;
}

Matrix Matrix::operator + (const Matrix &other)
{
	int p;
        if ((this->n != other.n) || (this->m != other.m))
        {
                throw Exception (3, "Размеры матриц не согласованы");
        }

	p = (other.n) * (other.m);

        for (int i=0; i < p; i++)
        {
//printf ("%d -->", array[i]);
		array[i] = array[i] + other.array[i];
//printf ("%d \n", array[i]);
        }
        return *this;
}

void Matrix::print() const
{
        for (int i=0; i<m; i++)
        {
		for (int j=0; j<n; j++)
        	{
                	printf ("%d ", array[j + (i)*n]);
        	}

        printf ("\n");

	}
}

Matrix Matrix::operator = (const Matrix &other)
{
        if ((this->n != other.n) || (this->n != other.n))
        {
                throw Exception (4, "Невозможно присвоить");
        }
        for (int i=0; i < (this->m)*(this->n); i++)
        {
		this->array[i] = other.array[i];

        }
        return *this;
}

int Matrix::Rows()
{
        return this ->m;
}

int Matrix::Columns()
{
        return this ->n;
}

int Matrix::GetElement(int i, int j)
{
	if (i < 0 || j < 0 || i >=m || j >= n)
        {
                throw Exception (1, "Неверные параметры");
        }
        return array [i*n+j];
}

Submatrix::Submatrix(Matrix *array,  int k, int l, int i, int j)
{

	array_ = array;
        n_ = l;
        m_ = k;
        i_ = i;
        j_ = j;

        if (k+i > array ->Rows() || l+j > array ->Columns() || i < 0 || j < 0 || k <= 0 || l <= 0)
        {
                throw Exception (1, "Неверные параметры");
        }
}

int Submatrix::Get_Element(int row, int column)
{

	if (row > m_+i_ || column > n_ + j_ || row < i_ || column < j_)
        {
                throw Exception (1, "Неверные параметры");
        }

        return array_ ->GetElement(i_ + row, j_ + column);
}
