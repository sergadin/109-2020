#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"rank.h"

double rank(double **mas, int n_rows, int n_cols)
{
	int k, j, i;
	double r = n_rows, t = 0, s = 0, d = 0;
	for (k = 0; k < n_rows; k ++)
	{
		for (i = k + 1; i < n_rows; i ++)
		{
			d = mas[k][k]; 
			if (d == 0)
				break;
			s = mas[i][k] / d;
			for (j = 0; j < n_cols; j ++)
			{
				mas[i][j] -= mas[k][j] * s;
			}
		}
	}
	for (k = n_rows-1; k >= 1; k --)
	{
		for (i = n_cols-1; i >= 0; i --)
		{
			d = mas[k][i]; 
			if (d == 0)
				break;
			mas[k-1][i] -= mas[k][i]*mas[k-1][i]/d;
		}
	}
	for(i = 0; i < n_rows; i++)
	{
		t=0;
		for(j = 0; j < n_cols; j++)
		{
			if(mas[i][j] == 0)
			{
				t=t+1;
			}
		}
		if(t == n_cols)
		{
			r=r-1;
		}
	}
	if (r == 0)
		r = 1;
	return r;
}








