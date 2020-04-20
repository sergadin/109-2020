#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"obr.h"
#define EL(ncol, col, row)\
	((ncol)*(row) + (col))

void obr(double *matr, int n, double * edmatr, double * NUL)
{
	int k, j, i;
	double c;
	for (k = 0; k < n - 1; k++)
	{
		for(int m = k; m < n; m ++)
		{
			if(matr[EL(n, m, k)] > matr[EL(n, k, k)])
			{
				for(int t = 0; t < n; t++)
				{	
					c = matr[EL(n, m, t)];
					matr[EL(n, m, t)] = matr[EL(n, k, t)];
					matr[EL(n, k, t)] = c;
					c = edmatr[EL(n, m, t)];
					edmatr[EL(n, m, t)] = edmatr[EL(n, k, t)];
					edmatr[EL(n, k, t)] = c;

				}
			}
		}

		if(fabs(matr[EL(n, k, k)]) > 0.0001)
		{
		
			for(j = n - 1; j >= 0; j--)
			{
				c = matr[EL(n, k, k)];
				matr[EL(n, k, j)] /= c;
				edmatr[EL(n, k, j)] /= c;
			}
			for(i = k + 1; i < n; i++)
			
				for(j = n - 1; j >= 0; j--)
				{
					c = matr[EL(n, i, k)];
					matr[EL(n, i, j)] -= matr[EL(n, k, j)] * c;
					edmatr[EL(n, i, j)] -= edmatr[EL(n, k, j)] * c;
				}
		}		

	}

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			c = matr[EL(n, i, i)];
			matr[EL(n, i, j)] /= c;
			edmatr[EL(n, i, j)] /= c;
		}
	}
	
	for(i = n - 1; i >= 0; i --)
	{
		for(j = 0; j < i; j++)
		{
			for(k = 0; k < n; k ++)
			{
				c = matr[EL(n, j, i)];
				matr[EL(n, j, k)] -= matr[EL(n, i, k)]*c;
				edmatr[EL(n, j, k)] -= edmatr[EL(n, i, k)]*c;
			}

		}
	}
				
}


