#include <stdio.h>
#include <stdlib.h>

#include "clin.h"

int main(void)
{
	FILE *fin, *fout;
	int n, m;
	double *matrix;
	ErrorCode materr;
	if ((fin = fopen("input.txt", "r")) == NULL)
		{
			printf("Input file error");
			return -1;
		}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		printf("Output file error");
		fclose(fin);
		return -1;
	}
	if ((fscanf(fin, "%d %d", &n, &m) != 2) || (n <= 1) || (m <= 1))
	{
		fprintf(fout, "Invalid data");
		fclose(fin);
		fclose(fout);
		return -1;
	}
	if ((matrix = (double *) malloc(n * m * sizeof(double))) == NULL)
	{
		fprintf(fout, "Allocation error");
		fclose(fin);
		fclose(fout);
		return -1;
	}
	read_matrix(matrix, n, m, fin, &materr);
	if (materr == DATAERR)
		{
		fprintf(fout, "Invalid data");
		fclose(fin);
		fclose(fout);
		free(matrix);
		return -1;
		}
	foundandtrans(matrix, n, m);
	print_matrix(matrix, n, m, fout);
	fclose(fin);
	fclose(fout);
	free(matrix);
	return 0;
}
