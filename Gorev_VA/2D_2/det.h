#define eps 0.0000001

double Abs(double x);
void centr_sym(double **matr, int n);
void swap(double **matr, int n, int i1, int i2);
void multiply(double **matr, int n, int i1, double c);
void plus_str(double **matr, int n, int i1, int i2, double c);
double det(double **A, int n);