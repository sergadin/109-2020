#include <stdio.h>
#include <stdlib.h>

#include "process.h"

#define MATR(m, i, j) matrix[(m) * (i) + (j)]

void read_matrix(double *matrix, int n, int m, FILE *fin, ErrorCode *materr)
{
		*materr = MATRIX_OK;
		for (int i = 0; i < m * n; i++)
	{
	if ((fscanf(fin, "%lf", &matrix[i]) != 1))
	{
		*materr = DATAERR;
		break;
	}
	}

}
void founding_and_transformation(double *matrix, int n, int m)
{
	int keyrow = -1;
	double strsum, minsum = 0, cursum = 0, memory;
	for (int i = 0; i < n; i++)
	{
		strsum = 0;
		cursum = 0;
		for (int j = 0; j < m; j++)
		{
			strsum += MATR(m, i, j);
		}
	for (int j = 0; j < m; j++)
	{
	if (MATR(m, i, j) > strsum/m)
		{
			cursum += MATR(m, i, j);
		}
	}
	if ((cursum < minsum) || (i == 0))
	{
		minsum = cursum;
		keyrow = i;
	}
}
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < m - i - 1; j++)
		{
		if(MATR(m, keyrow, j) <= MATR(m, keyrow, (j + 1)))
			{
			memory = MATR(m, keyrow, (j + 1));
			MATR(m, keyrow, (j + 1)) = MATR(m, keyrow, j);
			MATR(m, keyrow, j) = memory;
			}
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
			if (j != m - 1)
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
