#include "task.h"
#include "math.h"
#include <stdio.h>

int rank(double *data, int n_rows, int n_cols)
{
	int k = 0, l = 0, i, j;

	while(1)
	{
		printmat(data, n_rows, n_cols);

		//Ищем первый ненулевой столбец
		for(i = 0; i < n_cols; i++)
		{
			l = 0;
			for(j = k; j < n_rows; j++)
			{
				if(!(fabs(EL(data, n_cols, j, i)) < eps))
				{
					l = 1;
					break;
				}
			}
			if(l == 1)
				break;
		}
		if(l == 0)
		{
			fprintf(stdout,"we haven't found non-zero column :(\n");
			k -= 1;
			break;
		}
		fprintf(stdout,"we found non-zero column #%d\n",i+1);
		//Если в нём верхний элемент ноль, то меняем строчки так, чтобы был не ноль
		if(fabs(EL(data, n_cols, k, i)) < eps)
			swaprows(data, n_cols, k, j);
		//Обнуляем все нижние элементы столбца
		for(j = k+1; j < n_rows; j++)
		{
			if(!(fabs(EL(data, n_cols, j, i)) < eps))
			{
				plusrows(data, n_cols, j, k, (-EL(data, n_cols, j, i)) / EL(data, n_cols, k, i));
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
