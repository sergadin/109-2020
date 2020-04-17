#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	double e = 0.1, result = 0, current = 0;
	double b[] = {2};

	int i, j, n_rows = 3, n_cols = 4;
	double **matrix2d = malloc(n_rows* sizeof(double));
	FILE *input;
	if((input = fopen("input.txt", "r")) == NULL)
	{
		return -1;
	}
	for(int row = 0; row < n_rows; row++)
	{
		matrix2d[row] = malloc(n_cols* sizeof(double));
	}
	for(int i = 0; i < n_rows; i ++)
	{
		for(int j = 0; j < n_cols; j ++)
		{
			fscanf(input, "%lf", &current);
			matrix2d[i][j] = current;
		}
	}
	result = clin(matrix2d, n_rows, n_cols);
	printf("%lf\n", result);
	for(int row = 0; row < n_rows; row ++)
	{
		free(matrix2d[row]);
	}
	free(matrix2d);
	return 0;
}

double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
