#include "libs.h"

static double test_f(double x) {
    return x*x/(1-x);
}

int main() {
    cout << "n = ";
    rms_approximation first;
    cin >> first.n;
    cout << endl;
    first.f = test_f;
    first.Cin_x();
    double x;
    cout << "x = ";
    cin >> x;
    cout << "f(x) = " << test_f(x) <<"\nres = " << first.Calc_in_x(x) << endl;
    first.free_memory(); 
}
