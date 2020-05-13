#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "f.h"

int main(void)
{
	int i, j, n_rows = 5, n_cols = 5;
	double current;
	double *mas = malloc(n_rows*n_cols* sizeof(double));
	mas[] = {1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1};
	double result;
	/*FILE *input;
	if((input = fopen("input.txt", "r")) == NULL)
	{
		return -1;
	}
	for(i = 0; i < n_rows*n_cols ; i++)
	{
		fscanf(input, "%lf", &current);
		mas[i] = current;
	}
	fclose(input);
	*/
	result = rankA(mas, n_rows, n_cols);
	printf( "%lf\n", result);
	free(mas);
	return 0;
}


