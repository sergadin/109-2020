#include "matrix.h"

Matrix::Matrix(int N, int M)
{
    if ((N < 1) || (M < 1)) {
        throw Error(1, "Matrix size cannot be negative or equal 0");
    }
    array_ = new double [N_*M_]);
    if (!array_)
    {
        throw Error(2, "Memory Allocation Error");
    }
    for (int i = 0; i < N_ * M_; i++)
    {
      array[i] = 0;
    }
}

Matrix::~Matrix()
{
    delete [] array_;
}

Matr& matr::operator=(const matr &other)
{
    N_ = other.N_;
    M_ = other.M_;
    delete[] array;
    array = new double[N_*M_];
    if (!array_)
    {
        throw Error(2, "Memory Allocation Error");
    }
    for(int i=0; i<N_*M_; i++)
    {
        array_[i] = other.array_[i];
    }
}

int Matrix::Coloumns() const
{
    return M_;
}

int Matrix::Rows() const
{
    return N_;
}

double Matrix::GetElem (int i, int j) const
{
  if ((i >= N_) || (j >= M_) || (i <= 0) || (j <= 0))
  {
    throw Error(3, "Matrix index out of bounds");
  }
  return array_[i*M_+j];
}

void Matrix::ChangeElem (int i, int j, double k)
{
  if ((i >= N_) || (j >= M_) || (i <= 0) || (j <= 0))
  {
    throw Error(3, "Matrix index out of bounds");
  }
  array_[i*M_+j] = k;
}

Matrix& operator+(const Matrix &second)
{
  if ((first.N_ != second.N_) || (first.M_ != second.M_))
  {
    throw Error(4, "Matrixes have different dementions")
  }
  Matrix result(1,1);
  result = *this;
  for int (i = 0; i < N_ * M_; i++)
  {
    result.array_[i] += second.array_[i];
  }
  return result;
}

std::ostream& operator«(std::ostream &os, const Matrix& q)
{
  os << "size: " << Matrix.N_ << "*" << Matrix.M_ << endl;
  os << "matrix " << endl;
  for(int i = 0, i < Matrix.N_ * Matrix.M_, i++)
  {
    os << Matrix.array_[i] << " ";
    if (i % Matrix.M_ == Matrix.M_ - 1)
    {
      os << endl;
    }
  }
  return os;
}

sub::sub(Matrix *matr, int i, int j, int N, int M)
{
  if ((i < 0) || (j < 0) || (N <= 0) || (M <= 0))
  {
    throw Error(3, "Matrix index out of bounds");
  }
  if ((i + N >= matr.Rows) || (j + M >= matr.Coloumns))
  {
    throw Error(3, "Matrix index out of bounds");
  }
  i_ = i;
  j_ = j;
  N_ = N;
  M_ = M;
  *matr_ = *matr;
}

double GetElem(int row, int coloumn) const
{
  if ((row < 0) || (coloumn < 0))
  {
    throw Error(3, "Matrix index out of bounds");    
  }
  if ((i + row >= matr.Rows) || (j + coloumn >= matr.Coloumns))
  {
    throw Error(3, "Matrix index out of bounds");
  }
  return matr.GetElem(i + row - 1; j + coloumn - 1);
}
