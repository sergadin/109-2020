#include "libs.h"

static double test_f(double x) {
    return x*x/(1-x);
}

int main() {
    rms_approximation first;
    cout <<"We approximate the function X^2/(1-x) by linear function" << endl << endl;
    try {
        first.Addxy(5,test_f(5));
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    try { 
        first.Addxy(6,test_f(6));
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    try {
        first.Addxy(7,test_f(7));
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    try { 
        first.Addxy(8,test_f(8));
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    try {
        first.Addxy(9,test_f(9));
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    first.Cout_table();
    cout << endl;
    double x = 8.5;
    double res;
    try {
        res = first.Calc_in_x(x);
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    cout << "In point x = " << x << endl;;
    cout << "f(x) = " << test_f(x) <<"\nres = " << res << endl;
    return 0;
}
