#include "libs.h"

void rms_approximation::Make_matrix() {
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            matrix[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        matrix[0][0] += x[i]*x[i];
    }
    for (int i = 0; i < n; i++) {
        matrix[0][1] += x[i];
    }
    for (int i = 0; i < n; i++) {
        matrix[0][2] += x[i]*y[i];
    }
    matrix[1][0] = matrix[0][1];
    matrix[1][1] = n;
    for (int i = 0; i < n; i++) {
        matrix[1][2] += y[i];
    }
}
void rms_approximation::Calculate(){
    double det_m = matrix[0][0] * matrix[1][1] - matrix[0][1]*matrix[1][0];
    double det_a = matrix[0][2] * matrix[1][1] - matrix[0][1]*matrix[1][2];
    double det_b = matrix[0][0] * matrix[1][2] - matrix[0][2]*matrix[1][0];
    if (det_m == 0) {
        throw UserException(3, "Can't find a, b for approximate this function by linear function");
        return;
    }
    a = det_a / det_m;
    b = det_b / det_m;
}
rms_approximation::rms_approximation() {
    n = 1;
    x = (double*)malloc(1*sizeof(*x));
    if (!x) {
        throw UserException(1, "Memory Allocation Error");
    }
    y = (double*)malloc(1*sizeof(*y));
    if (!y) {
        throw UserException(1, "Memory Allocation Error");
    }
}
void rms_approximation::Cout_table() {
    cout << "x     y\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "   " << y[i] << endl;
    }
}
void rms_approximation::Print_matrix() {
    this -> Make_matrix();
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    try {
        this->Calculate();
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return;
	}
    cout << "a = " << a << " b = " << b << endl;
}
double rms_approximation::Calc_in_x(double x){
    this-> Make_matrix();
    try {
        this->Calculate();
    } catch (UserException &e) {
		cerr << "ERROR!:" << endl << e.message() << endl;
        return -1;
	}
    return a*x+b;
}
void rms_approximation::Addxy(double valueX, double valueY){
    static int i = 1;
    x =(double*)realloc(x, sizeof(*x) * i);
    if (!x) {
        throw UserException(2, "Memory Allocation Error");
        return;
    }
    y =(double*)realloc(y, sizeof(*x) * i);
    if (!y) {
        throw UserException(2, "Memory Allocation Error");
        return;
    }
    x[i-1] = valueX;
    y[i-1] = valueY;
    n = i;
    i++;
}
rms_approximation::~rms_approximation(){
        free(x);
        free(y);
}

UserException::UserException(int code, string message) : code_(code), message_(message) {}

string UserException::message() const {
	return message_;
}

int UserException::code() const {
	return code_;
}
