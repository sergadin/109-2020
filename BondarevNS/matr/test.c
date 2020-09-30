#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "clin.h"
#define MAX(a, b) (((a) > (b))?(a):(b))
#define MAX1(a, b, c) MAX(a, MAX(b, c))
double modul(double x);

int main(void)
{
	int row, i, j, n_rows = 3, n_cols = 4;
	double current, e = 0.1;
	double **mas = malloc(n_rows* sizeof(double));
	okrank = 4;
	FILE *input;
	if((input = fopen("input.txt", "r")) == NULL)
	{
		return -1;
	}
	for(row = 0; row < n_rows; row++)
	{
		mas[row] = malloc(n_cols* sizeof(double));
	}
	for(i = 0; i < n_rows ; i ++)
	{
		for(j = 0; j < n_cols; j ++)
		{
			fscanf(input, "%lf", &current);
			mas[i][j] = current;
		}
	}
	x = rank(mas, n_rows, n_cols, x);

		if (modul(x - b) < e)
		{
			printf("OK\n");
		}
		else
		{
			printf("NO OK\n");
		}
	}
	for(row = 0; row < n_rows; row ++)
	{
		free(mas[row]);
	}
	free(mas);
	fclose(input);
	return 0;
}


double modul(double x)
{
	if (x < 0)
		return -x;
	else 
		return x;
}
