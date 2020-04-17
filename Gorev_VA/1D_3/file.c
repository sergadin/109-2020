#include <stdio.h>
#include <stdlib.h>

void print_matrix(double *matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%e ", matr[i * n + j]);
		printf("\n");
	}
}

double *transp(double *matr, int m, int n)
{
	double *M;
	M = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i * m + j] = matr[j * n + i];
	return M;
}

double *inverse(double *A, int n)
{
	double *B;
	B = (double*)malloc(n * n * sizeof(double));

}

int main(void)
{
	double *matr, *MATR;
	int N = 2, M = 3;
	matr = (double*)malloc(N * M * sizeof(double));
	matr[0] = 0, matr[1] = 1, matr[2] = 2, matr[3] = 3, matr[4] = 4, matr[5] = 5;
	MATR = transp(matr, M, N);
	print_matrix(matr, M, N);
	printf("\n");
	print_matrix(MATR, N, M);

	printf("\n\n");

	MATR = transp(matr, N, M);
	print_matrix(matr, N, M);
	printf("\n");
	print_matrix(MATR, M, N);
	return 0;
}