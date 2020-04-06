#include <iostream>
#include <string.h>
#include <cstdio>
#include <math.h>
using namespace std;

typedef double (*FUN)(double);

class rms_approximation {
    private:
        double matrix[2][3];
        double a;
        double b;
        void Make_matrix();
        void Calculate();
        void Allocate_memory();
    public:
        double *x;
        int n;
        FUN f;
        void Cin_x();
        void Cout_table();
        void Print_matrix();
        void free_memory();
        double Calc_in_x(double x);
        void Setx(double x1, double x2, double x3, double x4, double x5);
};
