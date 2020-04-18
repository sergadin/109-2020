
#include<stdio.h>
#include"rank.h"
#define EL(ncol, row, col)\
	([(ncol)*(row) + (col)])

double * obr(double *matr, int n, double *edmatr)
{
	double maxa11, edmax11;
	double p = 0;
	double edp = 0;
	int cstr = 0, cel = 0;
	int q = 0;
	int i = -1;
	int maxstr;
	int stolb = n - 1;
	while((q <= n - 1) && (i < n))
	{
		i ++;		
		for(int j = (q + 1); j < n; j++)
		{
			if(matr[EL(n, j, i)] > matr[EL(n, q, i)])
			{
				for(int k = 0; k < n, k ++)
				{
					maxa11 = matr[EL(n, q, k)];
					matr[EL(n, q, k)] = matr[EL(n, j, k)];
					matr[EL(n, j, k)] = maxa11;

					edmaxa11 = edmatr[EL(n, q, k)];
					edmatr[EL(n, q, k)] = edmatr[EL(n, j, k)];
					edmatr[EL(n, j, k)] = edmaxa11;
				}
			}
		}
		if(matr[EL(n, q, i)] != 0)
		{
			for(int k = (q + 1); k < n; k++)
			{
				p =  matr[EL(n, k, i)]/matr[EL(n, q, i)];				
				edp =  edmatr[EL(n, k, i)]/edmatr[EL(n, q, i)];
				for(int t = i; t < n; t++)
				{
					matr[EL(n, k, t)] = matr[EL(n, k, t)] - p*matr[EL(n, q, t)];
					edmatr[EL(n, k, t)] = edmatr[EL(n, k, t)] - edp*edmatr[EL(n, q, t)];
				}
				
			}
			q = q + 1;
		}
		
	}


	for(int i = n - 1; i >= 0; i--)
	{
		for(int j = i + 1; j >= 0; j--)
		{
			matr[EL(n, j, stolb)] = 0;
			for(int k = n - 1; k >= 0; k --)
			{
			     edmatr[EL(n, j, k)] -= edmatr[EL(n, i, k)]*matr[EL(n, j, stolb)]/matr[EL(n, i, stolb)];

			}
		}
	stolb --;
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j ++)
		{
			edmatr[EL(n, i, j)] = edmatr[EL(n, i, j)]/matr[EL(n, i, i)];
		}
	}
return edmatr;



}



