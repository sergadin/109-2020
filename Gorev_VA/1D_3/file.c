#include <stdio.h>
#include <stdlib.h>
#include "inverse.h"

void print_matrix(double *matr, int m, int n);
void print_matrix(double *matr, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%g ", matr[i * n + j]);
		printf("\n");
	}
}

double *read_matrix(int m, int n, FILE* input);
double *read_matrix(int m, int n, FILE* input)
{
	double *matr;
	matr = (double*)malloc(m * n * sizeof(double));
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fscanf(input, "%lf", &matr[i * n + j]);
	return matr;
}

int main(void)
{
	return 0;
}
