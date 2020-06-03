#include <stdio.h>
#include <stdlib.h>
#include "read_matr.h"


int read_matr(double *a, char *name, int *N, int *M)
{
	FILE*fp;
	int n, m;
	
	fp = fopen(name,"r");
	if (!fp) return Open_Err;

	fscanf(fp, "%d %d\n", &n, &m);

	printf("%d %d", n, m);

	if (!(a = (double*) malloc (n*m*sizeof(double))))
	{
		printf("not enough memory\n");
		return Mem_Err;
	}
	printf("Lll\n");
	for (int i = 0; i < n*m; i++)
	{
		if (fscanf(fp,"%lf", &a[i])!=1)
		{
			fclose(fp);
			return Read_Err;
		}
	}

	if (!feof(fp))
	{
		fclose(fp);
		return Not_to_End;
	}

	*N = n;
	*M = m;
	printf("%d %d", n, m);
	fclose(fp);
	return All_Correct;
}
