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
	double *matr;
	int N = 3;
	ErrorCode *Error;
	FILE *input;
	Error = (ErrorCode*)malloc(sizeof(ErrorCode));

	matr = (double*)malloc(N * N * sizeof(double));
	if ((input = fopen("input.txt", "r")) == NULL)
	{
		return -1;
	}
	matr = read_matrix(N, N, input);

	print_matrix(matr, N, N);
	printf("\n");
	print_matrix(inverse(matr, N, Error), N, N);

	free(matr);
	free(Error);
	return 0;
}