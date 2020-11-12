#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

class matrix
{

	private:

		int N_, M_;
		double *array_;

	public: 

		matrix(int N, int M);
		~matrix();
		matrix& operator=(const matrix &other);

		int str() const;
		int stolb() const;
		void change(double t, int i, int j);
		double element(int i, int j) const;
		matrix operator+(const matrix &right);
		friend std::ostream&operator<<(std::ostream &os, const matrix& q);
};

class podmatrix
{

	private:

		int i;
		int j;
		int podN;
		int podM;
		matrix *podmatr;

	public:

		podmatrix(matrix *podmatr_, int i_, int j_, int n, int m);
		~podmatrix();

		double element(int n, int m) const;	
};

class iskl
{
	private:
		int code_;
		std::string message_;

	public:
		iskl(int code, std::string message):code_(code),message_(message){}
		std::string message() const{return message_;}
		int code()const{return code_;}
};
