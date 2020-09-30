#define eps 0.0000001

double ABS(double x);
void SwapRows(double **matrix, int n, int row1, int row2);
void PlusRow(double **matrix, int n, int row1, int row2, double c);
void MultRow(double **matrix, int n, int row, double c);
void Gauss(double **matrix, int n);
