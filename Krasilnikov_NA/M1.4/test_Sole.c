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
	double *ea, *ca, *determinant, *matrix; //ea = exact_answer, ca = calculated_answer
	double current;
	int definition;
	int i, j, n, memory;
	int cot; //count_of_tests
	int coct; //count_of_completed_tests
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
		coct = 0;
		fprintf(fout, "Test № %d:", (i + 1));
		if (((fscanf(fin, "%d", &n)) != 1) || (n < 1))
		{
			fprintf(fout, " LOSS | Invalid input file format");
			fclose(fin);
			fclose(fout);
			return -1;
		}
		if ((ea  = (double *) malloc(n * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			return -1;
		}
		if ((ca = (double *) malloc(n * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(ea);
			return -1;

		}
		if ((determinant = (double *) malloc(n * n * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			return -1;
		}
		if ((matrix  = (double *) malloc(n * (n + 1) * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
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
				free(ea);
				free(ca);
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
		for (j = 0; j < n; j++)
		{
			if (fscanf(fin, "%lf", &ea[j]) != 1)
			{
				fprintf(fout, " LOSS | Invalid input format");
				fclose(fin);
				fclose(fout);
				free(ea);
				free(ca);
				free(determinant);
				free(matrix);
				return -1;
			}
		}
		definition = definition_test(n, determinant, EPS/n);
		if (definition == 0)
		{
			fprintf(fout, " LOSS | System is not defined");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			free(determinant);
			free(matrix);
			return -1;
		}
		ca = find_solution(n, matrix, EPS/n);
		for (j = 0; j < n; j++)
		{
			if (fabs(ca[j] - ea[j]) < MAXOF3(fabs(ca[j]), fabs(ea[j]), 1) * EPS)
			{
				coct++;
			}
			else
			{
				break;
			}
		}
		if (coct == n)
		{
			fprintf(fout, " OK\nCalculated answer:\n");
			for (j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ca[j]);
			}
			fprintf(fout, "\nExact answer:\n");
			for (j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ea[j]);
			} 
		}
		else
		{
			fprintf(fout, " LOSS | Calculation error\nCalculated answer:\n");
			for (j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ca[j]);
			}
			fprintf(fout, "\nExact answer:\n");
			for (j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ea[j]);
			}
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			free(determinant);
			free(matrix);
			return -1;
		}
		fprintf(fout, "\n\n");
		free(ea);
		free(ca);
		free(determinant);
		free(matrix);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
