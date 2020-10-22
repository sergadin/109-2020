#include <cstdio>
#include <iostream>
#include <math.h>
using namespace std;

class Matrix{
	private:
		double *array_;
		int N_;
		int M_;
	public:
		Matrix(int N, int M);
		~Matrix();
		Matrix& operator =(const Matrix &other);
		int Coloumns () const;
		int Rows () const;
		double GetElem (int i, int j) const;
		void ChangeElem (int i, int j, double k);
		friend Matrix& operator+(const Matrix &second);
		friend std::ostream& operator«(std::ostream &os, const Matrix& q)
};

class sub{
	private:
		int i_;
		int j_;
		int N_;
		int M_;
		Matrix *matr_;

	public:
		sub(matr, i, j, N, M);
		~sub();
		double GetElem(int row, int coloumn);
};

class Error
{
	private:
		int EC_; //EC = Error_Code
		std::string reason_;

	public:
		Error(int EC, const std::string reason) : EC_(EC), reason_(reason) {}
		std::string reason() const
		{
			return reason_;
		}
		int EC() const
		{
			return EC_;
		}
};
