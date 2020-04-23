#include "task.h"
#include <math.h>
#include <stdio.h>

int rank(double *data, int n_rows, int n_cols)
{
	int k = 0, fail = 0, i = 0, j = 0;
	double max = 0;
	int maxrow, maxcol;

	while(!fail && k < n_rows)
	{
		printmat(data, n_rows, n_cols);
		fprintf(stdout,"\n");
		
		k++;
		fail = 1;
		max = 0;
		//Ищем максимальный по модулю элемент
		for(i = 0; i < n_cols; i++)
		{
			for(j = k-1; j < n_rows; j++)
			{
				if(!(fabs(EL(data, n_cols, j, i)) < eps))
					fail = 0;
				if(fabs(EL(data, n_cols, j, i)) > fabs(max))
				{
					max = EL(data, n_cols, j, i);
					maxrow = j;
					maxcol = i;
				}		
			}
		}

		if(fail)
		{
			k--;
		}
		else
		{
			swaprows(data, n_cols, k, maxrow);
			swapcols(data, n_rows, n_cols, k, maxcol);
			//Обнуляем все нижние элементы столбца
			for(j = k; j < n_rows; j++)
			{
				if(!(fabs(EL(data, n_cols, j, k-1)) < eps))
				{
					plusrows(data, n_cols, j, k-1, (-EL(data, n_cols, j, k-1)) / EL(data, n_cols, k-1, k-1));
				}
			}
		}
	}

	return k;
}

void swaprows(double *data, int n_cols, int row1, int row2)
{
	int i;
	double t;

	for(i = 0; i < n_cols; i++)
	{
		t = EL(data, n_cols, row1, i);
		EL(data, n_cols, row1, i) = EL(data, n_cols, row2, i);
		EL(data, n_cols, row2, i) = t;
	}
}
void swapcols(double *data, int n_rows, int n_cols, int col1, int col2)
{
	int i;
	double t;

	for(i = 0; i < n_rows; i++)
	{
		t = EL(data, n_cols, i, col1);
		EL(data, n_cols, i, col1) = EL(data, n_cols, i, col2);
		EL(data, n_cols, i, col2) = t;
	}
}
void plusrows(double *data, int n_cols, int row1, int row2, double k)
{
	int i;

	for(i = 0; i < n_cols; i++)
	{
		EL(data, n_cols, row1, i) += k * EL(data, n_cols, row2, i);
	}
}
void printmat(double *data, int n_rows, int n_cols)
{
	int i,j;
	for(i = 0; i < n_rows; i++)
	{
		for(j = 0; j < n_cols; j++)
		{
			fprintf(stdout,"%g ",EL(data, n_cols, i, j));
		}
		fprintf(stdout, "\n");
	}

}
