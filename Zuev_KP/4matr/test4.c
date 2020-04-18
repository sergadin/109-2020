#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"

int main(void)
{
	int i, j, n_rows = 3, n_cols = 4;
	double current;
	double **matrix2d = malloc(n_rows* sizeof(double));
	double *x1;
	FILE *input1;
	int o[n_rows];
	for ( i = 0; i < n_cols; i++ )
	{
		o[i] = i;
	}
	if((input1 = fopen("input1.txt", "r")) == NULL)
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
			fscanf(input1, "%lf", &current);
			matrix2d[i][j] = current;
		}
	}
	x1 = clin(matrix2d, n_rows, n_cols);
	for ( i = 0; i < n_rows; i++ )
	{
		for ( j = 0; j < n_rows; j++ )
		{
			if ( i == o[j] )
			{
				printf( "%lf\n", x1[j] );
				break;
			}
		}
	}
	for(int row = 0; row < n_rows; row ++)
	{
		free(matrix2d[row]);
	}
	free(matrix2d);
	return 0;
}
































