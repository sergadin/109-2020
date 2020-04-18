#include<math.h>
#include<stdio.h>
#include"rank.h"

double frank(double **matr, int n, int m)
{
	double * maxa11;
	double p = 0;
	int cstr = 0, cel = 0;
	int q = 0;
	int i = 0;
	int maxstr;
	while((q < n - 1) && (i < m - 1))
	{		
		for(int j = (q + 1); j < n; j++)
		{
			if(matr[j][i] > matr[q][i])
			{

				maxa11 = matr[q];
				matr[q] = matr[j];
				matr[j] = maxa11;
			}
		}
		if(matr[q][i] != 0)
		{
			for(int k = (q + 1); k < n; k++)
			{
				p =  matr[k][i]/matr[q][i];
				for(int t = i; t < m; t++)
				{
					matr[k][t] = matr[k][t] - p*matr[q][t]; 
				}
				
			}
			q = q + 1;
		}
	i++;	
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j ++)
		{
			if(matr[i][j] != 0)
				cel ++;

		}
		if(cel != 0)
			cstr = cstr + 1;
		cel = 0;
	}
	if(cstr == 0)
		return 1;
	else 
		return cstr;
}



