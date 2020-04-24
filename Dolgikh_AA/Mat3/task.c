#include "task.h"
#include <math.h>
#include <stdio.h>

int inv(double **matrix, double **matrixinv, int N)
{
	int curr_row = 0, i, j, non_zero_not_found = 0, I, J;

	//Делаем из второй матрицы единичную
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			if(i == j)
				matrixinv[i][j] = 1;
			else
				matrixinv[i][j] = 0;
		}
	}

	//Методом Гаусса приводим матрицу к унитреугольному виду
	while(!non_zero_not_found && curr_row < N)
	{
		non_zero_not_found = 1;

		//Ищем первый ненулевой столбец
		for(i = 0; i < N; i++)
		{
			for(j = curr_row; j < N; j++)
			{
				if(!(fabs(matrix[j][i]) < eps) && non_zero_not_found)
				{
					non_zero_not_found = 0;
					I = i;
					J = j;
				}
			}
		}
		if(!non_zero_not_found)
		{
			//Если в нём верхний элемент ноль, то меняем строчки так, чтобы был не ноль
			if(fabs(matrix[curr_row][I]) < eps)
			{
				swaprows(matrix, N, curr_row, J);
				swaprows(matrixinv, N, curr_row, J);
			}
			//И делаем верхний элемент единицей
			multrow(matrixinv, N, curr_row, 1/matrix[curr_row][I]);
			multrow(matrix, N, curr_row, 1/matrix[curr_row][I]);
			//Обнуляем все нижние элементы столбца
			for(j = curr_row + 1; j < N; j++)
			{
				if(!(fabs(matrix[j][I]) < eps))
				{
					plusrows(matrixinv, N, j, curr_row, (-matrix[j][I]) / matrix[curr_row][I]);
					plusrows(matrix, N, j, curr_row, (-matrix[j][I]) / matrix[curr_row][I]);
				}
			}
			curr_row++;
		}
	}

	if(!non_zero_not_found)
	{
		//Обратным ходом метода Гаусса превращаем матрицу в единичную
		for(i = N-1; i > 0; i--)
		{
			for(j = 0; j < i; j++)
			{
				plusrows(matrixinv, N, j, i, -matrix[j][i]);
				plusrows(matrix, N, j, i, -matrix[j][i]);
			}
		}
	}

	return 1 - non_zero_not_found;
}

void swaprows(double **matrix, int N, int row1, int row2)
{
	int i;
	double t;

	for(i = 0; i < N; i++)
	{
		t = matrix[row1][i];
		matrix[row1][i] = matrix[row2][i];
		matrix[row2][i] = t;
	}
}
void plusrows(double **matrix, int N, int row1, int row2, double k)
{
	int i;

	for(i = 0; i < N; i++)
	{
		matrix[row1][i] += k * matrix[row2][i];
	}
}
void multrow(double **matrix, int N, int row, double k)
{
	int i;
	for(i = 0; i < N; i++)
	{
		matrix[row][i] *= k;
	}

}
void printmat(double **matrix, int N)
{
	int i,j;
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
		{
			fprintf(stdout, "%g ", matrix[i][j]);
		}
		fprintf(stdout, "\n");
	}
}
