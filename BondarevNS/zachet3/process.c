#include <stdio.h>
#include <stdlib.h>

#include "process.h"

#define MATR(n, i, j) matrix[(n) * (i) + (j)]

void read_matrix(double *matrix, int n, int m, FILE *fin, ErrorCode *materr)
{
	*materr = MATRIX_OK;
	
		for(int i = 0; i< m * n; i++)
		{
			if((fscanf(fin, "%lf", &matrix[i]) != 1))
			{
				*materr = DATAERR;
				break;
			}
		}
	
	
}

void print_matrix(double *matrix, int n, int m, FILE *fout)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fprintf(fout, "%lf", MATR(m, i, j));
			if(j != m -1)
			{
				fprintf(fout, " ");
			}
		}
			if (i != n - 1)
			{
				fprintf (fout, "\n");		
			}
	}
}

void foundandtrans(double *matrix, int n, int m)
{
	int kr = -1, strcount = 0;
	double strsum, minsum = 0, cursum = 0, memory;
	for (int i = 0; i<n; i++)
	{
		strsum = 0;
		cursum = 0;
		for (int j = 0; j < m; j++)
		{
			strsum += MATR(m, i, j);
		}
		for (int j = 0; j<m; j++)
		{
			if (MATR(m, i, j)>strsum/m)
			{
				cursum += MATR(m, i, j);
				
			}
		}
		if ((i ==0) || (cursum < minsum))
		{
			minsum = cursum;
			kr = i;
		}
	
	}
	for(int i=0; i<m; i++)
	{
		for (int j =0; j< m - i - 1; j++)
		{
			if(MATR(m, kr, j) <= MATR(m, kr, (j + 1)))
			{
				memory = MATR(m, kr, (j+1));
				MATR(m, kr, (j+1)) = MATR(m, kr, j);
				MATR(m, kr, j) = memory;
			}
		}
	}
}
