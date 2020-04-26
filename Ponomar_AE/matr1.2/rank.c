#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include "rank.h"

#define min(a,b) ((a)<(b) ? (a) : (b))

void printMatrix(double **matrix, int n, int m);

int rank_matrix(double **matrix, int n, int m, double E)
{
	int rank = 0, curr_string = 0, k = 1;
	double max = 0;
	int max_string, max_column;

	while((k == 1) && (curr_string < min(n, m)))
	{
                k = 0;
                max = 0;
		for(int i = curr_string; i < n; i++)
		{
			for(int j = curr_string; j < m; j++)
			{
				if(fabs(matrix[i][j]) > fabs(max))
				{
					k = 1;
					max = matrix[i][j];
					max_string = i;
					max_column = j;
				}	
			}
		}

		if (k == 1)
		{
	                for(int j = curr_string; j < m; j++)
	                {
		                double change = matrix[curr_string][j];
		                matrix[curr_string][j] = matrix[max_string][j];
		                matrix[max_string][j] = change;
	                }
                        for(int i = curr_string; i < n; i++)
	                {
		                double change = matrix[i][curr_string];
		                matrix[i][curr_string] = matrix[i][max_column];
		                matrix[i][max_column] = change;
	                }

			for(int i = curr_string + 1; i < n; i++)
			{
				if(fabs(matrix[curr_string][curr_string]) > E)
				{
                                        double factor = matrix[i][curr_string] / matrix[curr_string][curr_string];
                                     	for(int j = curr_string; j < m; j++)
	                                {
                                                matrix[i][j] -= matrix[curr_string][j] * factor;
                                                                      
                                        }
				}
			}
                        
			curr_string++;
		}
	}

        return curr_string;
}


void printMatrix(double **matrix, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%lf ", matrix[i][j]);
		}
		printf("\n");
	}
}
