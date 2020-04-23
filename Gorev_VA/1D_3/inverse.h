typedef enum { OK = 0, MATR_IS_SINGULAR } ErrorCode;
#define eps 0.0000001

double Abs(double x);
void centr_sym(double *matr, int n);
void swap(double *matr, int n, int i1, int i2);
void multiply(double *matr, int n, int i1, double c);
void plus_str(double *matr, int n, int i1, int i2, double c);
void diag(double *A, double *A_dop, int n, ErrorCode *Error);
void inverse(double *A, int n, ErrorCode *Error);

void print_matrix(double *matr, int m, int n);
double *read_matrix(int m, int n, FILE* input);