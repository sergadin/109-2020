#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"

int main(void)
{
	int i, j, n_rows = 3, n_cols = 4;
	double current;
	double **matrix2d = malloc(n_rows* sizeof(double));
	double *x;
	int otv[n_rows];
	for ( i = 0; i < n_cols; i++ )
		otv[i] = i;
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

	x = clin(matrix2d, n_rows, n_cols);
	printf( "Ответ:\n" );
	for ( i = 0; i < n_rows; i++ )
		for ( j = 0; j < n_rows; j++ )
			if ( i == otv[j] )
			{
				printf( "%f\n", x[j] );
				break;
			}
	for(int row = 0; row < n_rows; row ++)
	{
		free(matrix2d[row]);
	}
	free(matrix2d);
	return 0;
}
































