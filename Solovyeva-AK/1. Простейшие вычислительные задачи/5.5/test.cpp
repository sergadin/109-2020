#include "libs.h"

static double test_f(double x) {
    return x*x/(1-x);
}

int main() {
    rms_approximation first;
    first.f = test_f;
    cout <<"We approximate the function X^2/(1-x) by linear function" << endl << endl;
    first.Setx(5,6,7,8,9);
    first.Cout_table();
    cout << endl;
    double x = 8.5;
    cout << "In point x = " << x << endl;;
    cout << "f(x) = " << test_f(x) <<"\nres = " << first.Calc_in_x(x) << endl;
    first.free_memory(); 
}
