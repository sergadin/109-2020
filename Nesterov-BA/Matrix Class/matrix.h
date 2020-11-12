#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

class matrix
{
	private:
		int n_;
		int m_;
		double *elements_;
	public:
		matrix(int n, int m);
		~matrix();
		matrix& operator=(const matrix &other);
		int get_rows() const;
		int get_cols() const;
		double get_elem(int i, int j) const;
		void set_elem(double val, int i, int j);
		matrix operator+(const matrix &right);
		friend std::ostream& operator<<(std::ostream &os, const matrix& matr);
};

class submatrix
{
	private:
		int i_;
		int j_;
		int N_;
		int M_;
		matrix *matr_;
	public:
		submatrix(matrix *matr,int i,int j,int n,int m);
		~submatrix();
		double get_elem(int n, int m) const;	
};

class Exception {
	private:
		int code_;
		std::string message_;
	public:
		Exception(int code, std::string message) : code_(code), message_(message) {}
		std::string message() const {return message_;}
		int code() const {return code_;}
};
