#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;

class Matrix
{
	private:
		double *array_;
		int N_;
		int M_;
	public:
		Matrix(int N, int M);
		~Matrix();
		Matrix & operator=(const Matrix &other);
		int Rows() const;
		int Coloumns() const;
		double GetElem (int i, int j) const;
		void ChangeElem (int i, int j, double k);
		Matrix operator+(const Matrix &second);
		friend std::ostream& operator <<(std::ostream &os, const Matrix& Matrix);
};

class sub
{
	private:
		int i_;
		int j_;
		int N_;
		int M_;
		Matrix *matr_;
	public:
		sub(Matrix *matr, int i, int j, int N, int M);
		~sub();
		double GetElem(int row, int coloumn) const;
};

class Error
{
	private:
		int EC_;
		std::string reason_;
	public:
		Error(int EC, std::string reason) : EC_(EC), reason_(reason) {}
		std::string reason() const 
		{
			return reason_;
		}
		int code() const
		{
			return EC_;
		}
};
