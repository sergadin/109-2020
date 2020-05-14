#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"
#define min(a,b) ((a)<(b) ? (a) : (b))
#define el(m, n_cols, row, col) \
    ((m)[(n_cols) * (row) + col])
#define eps = 0.0001
double ab (double m) 
{
	if(m < 0)
	{
		return -m;
	}
	else
	{
		return m;
	}
}

int find (*double data, int col, int row, int n_rows, int n_cols)
{
	int j = -1, temp, cons;
	\\ищем ненулевой элемент
	for(int m = row; m < n_rows; m++)
	{
		if(ab(el(data, n_cols, row, col)) > eps)
		{
			j = m;
		}
	}
	if(j == -1)
	{
		return 0;
	}
	\\меняем строки местами
	for(int m = col; m < n_cols; m++)
	{
		temp = el(data, n_cols, row, m);
		el(data, n_cols, row, m) = el(data, n_cols, j, m);
		el(data, n_cols, j, m) = temp;
	}
	temp = el(data, n_cols, row, col);
	\\вычитаем первую из последующих 
	for(int m = j + 1; m < n_rows; m++)
	{
		if(ab(el(data, n_cols, m, col)) > eps)
		{
			
			for(int c = col, c < n_cols; c++)
			{
				el(data, n_cols, m, c) *= temp;
				el(data, n_cols, m, c) -= el(data, n_cols, row, c) * el(data, n_cols, m, col);
			}
		}	
	}
	return 1;
}

double rank_A (*double data, int n_rows, int n_cols)
{
	int k = min(n_rows, n_cols), col = 0, row = 0, rank = 0;
	for(col < k; col++)
	{
		row += find(data, col, row, n_rows, n_cols);		
	}
	for(int j = 0; j < n_rows;j++)
	{
		if(el(data, n_cols, j, rank) > eps)
		{
			rank++;
		}
	}
	return rank;
}

