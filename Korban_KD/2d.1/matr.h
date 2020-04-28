#define MATRIX_H

int read_matrix(double *a, int m, int n, const char *name);

enum MATR_RETURN_CODES
{
	MATR_SUCCESS = 1,
	MATR_ERR_OPEN = -2,
	MATR_ERR_READ,
};

double f1(int n, int i, int j);
double f3(int n, int i, int j);
double f4(int n, int i, int j);
void init_matrix(double *a, int n, int k);
void init_vector(double *b, double *a, int n);
void print_matrix(double *a, int n, int m);
void print_vector(double *a, int n, int m);
void transpos(double *a,int m, int n);
void colum_swap(double *a,int m, int n, int i, int j );
void row_swap(double *a,int m, int n, int i, int j );
void delete_part(double *a, int m, int n, int i, int j);
void row_substr(double *a,int m, int n, int i, int j, double b );
double norm_matrix(double *a, int n);
void mult_vector(double *a, double *b, double *c, int m, int n);
double find_determinant (int n, double *a );
double find_max_abs_redused_colum(int n, double *a, int start,int *max_i);
void mult_matrix(double *a, double *b, double *c, int m, int n, int k);double find_max_abs_redused(int n, double *a, int start, int  *max_i, int *max_j);
