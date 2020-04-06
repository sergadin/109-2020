#include <iostream>
#include <string>
#include <cstdio>
#include <math.h>
using namespace std;

typedef double (*FUN)(double);

class rms_approximation {
    private:
        int n;
        double *x;
        double *y;
        double matrix[2][3];
        double a;
        double b;
        void Make_matrix();
        void Calculate();
    public:
        rms_approximation();
        void Cout_table();
        void Print_matrix();
        double Calc_in_x(double x);
        void Addxy(double valueX, double valueY);
        ~rms_approximation();
};

class UserException {
	private:
		int code_;
		string message_;
	public:
		UserException(int code, string message);
		string message() const;
		int code() const;
};
