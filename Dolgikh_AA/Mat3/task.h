#define eps 0.000001

int inv(double **matrix, double **matrixinv, int N);
void swaprows(double **matrix, int N, int row1, int row2);
void plusrows(double **matrix, int N, int row1, int row2, double k);
void multrow(double **matrix, int N, int row, double k);
void printmat(double **matrix, int N);
