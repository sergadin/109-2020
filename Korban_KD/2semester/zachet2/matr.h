#define MATRIX_H

int read_matrix(double *a, int m, int n, const char *name);

enum MATR_RETURN_CODES
{
	MATR_SUCCESS = 1,
	MATR_ERR_OPEN = -2,
	MATR_ERR_READ,
};

void print_matrix(double *a, int n, int m);
