#include "task.h"
#include <math.h>
#include <stdio.h>

int rank(double *data, int n_rows, int n_cols)
{
	int k = 0, fail = 1, i, j;
	double max = 0;
	int maxrow, maxcol;

	while(1)
	{
		printmat(data, n_rows, n_cols);
		
		fail = 1;
		//Ищем максимальный по модулю элемент
		for(i = 0; i < n_cols; i++)
		{
			for(j = k; j < n_rows; j++)
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
			fprintf(stdout,"we haven't found non-zero column :(\n");
			k--;
			break;
		}
		fprintf(stdout,"we found non-zero column #%d\n",maxcol+1);
		swaprows(data, n_cols, k, maxrow);
		swapcols(data, n_rows, n_cols, k, maxcol);
		//Обнуляем все нижние элементы столбца
		for(j = k+1; j < n_rows; j++)
		{
			if(!(fabs(EL(data, n_cols, j, k)) < eps))
			{
				plusrows(data, n_cols, j, k, (-EL(data, n_cols, j, k)) / EL(data, n_cols, k, k));
			}
		}

		if(k == n_rows - 1 || i == n_cols - 1)
			break;
		else
			k++;
	}

	return k + 1;
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
