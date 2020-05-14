#include "task.h"
#include <math.h>
#include <stdio.h>

int rank(double *data, int n_rows, int n_cols)
{
	int curr_row = 0, non_zero_found = 1;
	double max = 0;
	int maxrow, maxcol;

	while(non_zero_found && curr_row < n_rows)
	{
		printmat(data, n_rows, n_cols);
		fprintf(stdout,"\n");
		
		non_zero_found = 0;
		max = 0;
		//Ищем максимальный по модулю элемент
		for(int i = 0; i < n_cols; i++)
		{
			for(int j = curr_row; j < n_rows; j++)
			{
				if(fabs(EL(data, n_cols, j, i)) > fabs(max))
				{
					non_zero_found = 1;
					max = EL(data, n_cols, j, i);
					maxrow = j;
					maxcol = i;
				}		
			}
		}

		if(non_zero_found)
		{
			swaprows(data, n_cols, curr_row, maxrow);
			swapcols(data, n_rows, n_cols, curr_row, maxcol);
			//Обнуляем все нижние элементы столбца
			for(int j = curr_row+1; j < n_rows; j++)
			{
				if(!(fabs(EL(data, n_cols, j, curr_row)) < eps))
				{
					plusrows(data, n_cols, j, curr_row, (-EL(data, n_cols, j, curr_row)) / EL(data, n_cols, curr_row, curr_row));
				}
			}
			curr_row++;
		}
	}

	return curr_row;
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
