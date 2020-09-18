#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "zachet3.h"


void SwapRows(double *matrix, int row_length, int row1, int row2)
{
	double a;
	int i;
	for(i = 0; i<row_length; ++i)
		{
			a = matrix[row1*row_length + i];
			matrix[row1*row_length + i] = matrix[row2*row_length + i];
			matrix[row2*row_length + i] = a;
		}
}

double ScalarMult(double *matrix, int RowLength, int row1, int row2)
{
	int i;
	double result;
	result = 0;
	for (int i = 0; i < RowLength; i++)
	{
		result += matrix[row1*RowLength+i] * matrix[row2*RowLength+i];
	}
	return result;
}

double SoughtRow(double *matrix, int n, int m)
{
	int position, min_position, sought_row;
	min_position = m;
	sought_row = -1;
	double max_elem;
	for (int k = 0; k < n; k++)
	{
		max_elem = -1000000;
		for (int i = 0; i < m; i++)
		{
		fprintf(stdout, "max %lf \n", max_elem);
			if (matrix[k*m+i] > max_elem)
			{
				max_elem = matrix[k*m+i];
				position = i;
				fprintf(stdout, "position %d \n", position);
			}
		}
		if(position < min_position)
		{
			min_position = position;
			sought_row = k;
			fprintf(stdout, "%d \n", sought_row);
		}
	}

	return sought_row;
}

void transform(double *matrix, int n, int m)
{
	int sought_row;
	double scalars[n];
	double temp;
	sought_row = SoughtRow(matrix, n, m);
	
	for(int i = 0; i < n; ++i)
	{
		scalars[i] = ScalarMult(matrix, m, i, sought_row);
	}
	
	for (int c = 0 ; c < n - 1; c++)
	{
		for (int d = 0 ; d < n - c - 1; d++)
    		{
      			if (scalars[d] > scalars[d+1])
      			{
        			temp = scalars[d];
        			scalars[d] = scalars[d+1];
        			scalars[d+1] = temp;
        			SwapRows(matrix, m, d, d+1);
      			}
    		}
  	}
}
