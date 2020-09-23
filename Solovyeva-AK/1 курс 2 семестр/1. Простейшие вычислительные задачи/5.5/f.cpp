#include "libs.h"

void rms_approximation::Allocate_memory() {
    x = (double*)malloc(n*sizeof(double));
}
void rms_approximation::Cin_x() {
    this -> Allocate_memory();
    for(int i = 0; i < n; i++){
        cout << "x" << i <<" = ";
        cin >> x[i];
    }
}
void rms_approximation::Cout_table() {
    cout << "x     f(x)\n";
    for (int i = 0; i < n; i++) {
        cout << x[i] << "   " << f(x[i]) << endl;
    }
}
void rms_approximation::Make_matrix(){
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
        matrix[0][2] += x[i]*f(x[i]);
    }
    matrix[1][0] = matrix[0][1];
    matrix[1][1] = n;
    
    for (int i = 0; i < n; i++) {
        matrix[1][2] += f(x[i]);
    }
}

void rms_approximation::Print_matrix(){
    this -> Make_matrix();
    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    this->Calculate();
    cout << "a = " << a << " b = " << b << endl;
}

void rms_approximation::Calculate(){
    double det_m = matrix[0][0] * matrix[1][1] - matrix[0][1]*matrix[1][0];
    double det_a = matrix[0][2] * matrix[1][1] - matrix[0][1]*matrix[1][2];
    double det_b = matrix[0][0] * matrix[1][2] - matrix[0][2]*matrix[1][0];
    a = det_a / det_m;
    b = det_b / det_m;
}

double rms_approximation::Calc_in_x(double x){
    this-> Make_matrix();
    this-> Calculate();
    return a*x+b;
}

void rms_approximation::free_memory(){
    free(x);
}

void rms_approximation::Setx(double x1, double x2, double x3, double x4, double x5){
    n = 5;
    this->Allocate_memory();
    x[0] = x1;
    x[1] = x2;
    x[2] = x3;
    x[3] = x4;
    x[4] = x5;
}
