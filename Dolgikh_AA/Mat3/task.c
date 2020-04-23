#include "task.h"
#include <math.h>
#include <stdio.h>

int inv(double **matrix, double **matrixinv, int N)
{
	int k = 0, i, j, fail = 1;

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
	while(1)
	{
		//Ищем первый ненулевой столбец
		for(i = 0; i < N; i++)
		{
			fail = 1;
			for(j = k; j < N; j++)
			{
				if(!(fabs(matrix[j][i]) < eps))
				{
					fail = 0;
					break;
				}
			}
			if(!fail)
				break;
		}
		//Если унитреугольная не получается, возвращаем 0
		if(fail)
		{
			return 0;
		}
		//Если в нём верхний элемент ноль, то меняем строчки так, чтобы был не ноль
		if(fabs(matrix[k][i]) < eps)
		{
			swaprows(matrix, N, k, j);
			swaprows(matrixinv, N, k, j);
		}
		//И делаем верхний элемент единицей
		multrow(matrixinv, N, k, 1/matrix[k][i]);
		multrow(matrix, N, k, 1/matrix[k][i]);
		//Обнуляем все нижние элементы столбца
		for(j = k+1; j < N; j++)
		{
			if(!(fabs(matrix[j][i]) < eps))
			{
				plusrows(matrixinv, N, j, k, (-matrix[j][i]) / matrix[k][i]);
				plusrows(matrix, N, j, k, (-matrix[j][i]) / matrix[k][i]);
			}
		}

		if(k == N - 1 || i == N - 1)
			break;
		else
			k++;
	}

	//Обратным ходом метода Гаусса превращаем матрицу в единичную
	for(i = N-1; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			plusrows(matrixinv, N, j, i, -matrix[j][i]);
			plusrows(matrix, N, j, i, -matrix[j][i]);
		}
	}

	return 1;
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
