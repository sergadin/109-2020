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
	double *ea, *ca, *mos; //ea = exact_answer, ca = calculated_answer, mos = matrix_of_system
	int n, memory, cot, coct; //cot = count_of_tests, coct = count_of_completed_tests
	ErrorCode se; //se = system_error
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Output file doesn't exist");
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
	for (int i = 0; i < cot; i++)
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
		if ((mos  = (double *) malloc(n * (n + 1) * sizeof(double))) == NULL)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			return -1;
		}
		for (int j = 0; j < n * (n + 1); j++)
		{
			if (fscanf(fin, "%lf", &mos[j]) != 1)
			{
				fprintf(fout, " LOSS | Invalid input format");
				fclose(fin);
				fclose(fout);
				free(ea);
				free(ca);
				free(mos);
				return -1;
			}
		}
		for (int j = 0; j < n; j++)
		{
			if (fscanf(fin, "%lf", &ea[j]) != 1)
			{
				fprintf(fout, " LOSS | Invalid input format");
				fclose(fin);
				fclose(fout);
				free(ea);
				free(ca);
				free(mos);
				return -1;
			}
		}
		ca = solve_system(n, mos, EPS/n, &se);
		if (se == ALLOCATION_ERROR)
		{
			fprintf(fout, " LOSS | Memory allocation error");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			free(mos);
			return -1;
		}
		if (se == NOT_DEFINED)
		{
			fprintf(fout, " LOSS | System isn't defined");
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			free(mos);
			return -1;

		}
		for (int j = 0; j < n; j++)
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
			for (int j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ca[j]);
			}
			fprintf(fout, "\nExact answer:\n");
			for (int j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ea[j]);
			} 
		}
		else
		{
			fprintf(fout, " LOSS | Calculation error\nCalculated answer:\n");
			for (int j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ca[j]);
			}
			fprintf(fout, "\nExact answer:\n");
			for (int j = 0; j < n; j++)
			{
				fprintf(fout, "X_%d = %2.9f ", (j + 1), ea[j]);
			}
			fclose(fin);
			fclose(fout);
			free(ea);
			free(ca);
			free(mos);
			return -1;
		}
		fprintf(fout, "\n\n");
		free(ea);
		free(ca);
		free(mos);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
