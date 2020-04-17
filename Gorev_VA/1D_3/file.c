#include <stdio.h>
#include <stdlib.h>

void print_matrix(double *matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%f ", matr[i * n + j]);
		printf("\n");
	}
}


int main(void)
{
	double *matr;
	int N = 2;
	matr = (double*)malloc(N * N * sizeof(double));
	matr = { 0, 0, 0, 0 };
	print_matrix(matr, N, N);
	return 0;
}