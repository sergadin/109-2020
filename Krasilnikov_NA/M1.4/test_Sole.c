#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sole.h"

#define EPS 0.000001
#define MAXOF2(x, y) (((x) > (y)) ? (x) : (y))
#define MAXOF3(x, y, z) MAXOF2(x, MAXOF2(y, z))

int main(void)
{
	FILE *fin, *fout;
	double *answer, *determinant, *matrix;
	double current;
  int definition;
	int i, j, n, memory;
	int cot; //count_of_tests
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Outputfile doesn't exist");
		fclose(fin);
		return -1;
	}
	if ((fscanf(fin, "%d", &cot)) != 1)
	{
		fprintf(fout, "Invalid input file format");
		fclose(fin);
		fclose(fout);
		return -1;
	}
	for (i = 0; i < cot; i++)
	{
		fprintf(fout, "Test № %d:", (i + 1));
		if (((fscanf(fin, "%d", &n)) != 1) || (n < 1))
		{
			fprintf(fout, " LOSS | Invalid input file format");
			fclose(fin);
			fclose(fout);
			return -1;
		}
		if ((answer  = (double *) malloc(n * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			return -1;
		}
		if ((determinant = (double *) malloc(n * n * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(answer);
			return -1;
		}
		if ((matrix  = (double *) malloc(n * (n + 1) * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(answer);
			free(determinant);
			return -1;
		}
		for (j = 0; j < n * (n + 1); j++)
		{
			if (fscanf(fin, "%lf", &current) != 1)
			{
				fprintf(fout, " LOSS | Invalid input format");
				fclose(fin);
				fclose(fout);
				free(answer);
				free(determinant);
				free(matrix);
				return -1;
			}
			matrix[j] = current;
			if ((j % (n + 1)) != n)
			{
				memory = j;
				j = j - (j / (n + 1));
				determinant[j] = current;
				j = memory;
			}
		}
		definition = definition_test(n, determinant, EPS/n);
    find_solution(n, matrix, EPS/n);
		if (det == 0)
		{
			fprintf(fout, " LOSS | System is not defined");
			fclose(fin);
			fclose(fout);
			free(answer);
			free(determinant);
			free(matrix);
			return -1;
		}
		printf("%lf", det);
	}
}
