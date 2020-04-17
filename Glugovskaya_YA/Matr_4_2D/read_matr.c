#include <stdio.h>
#include <stdlib.h>
#include "read_matr.h"

int read_matr(double **a, int n, int m, char *name)
{
	FILE *fp;
	int i, j;
	fp = fopen(name,"r");
	if (!fp) return Open_Err;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			if (fscanf(fp,"%lf", &(a[i][j]))!=1) 
			{
				fclose(fp);
				return Read_Err;
			}			
		}
	}
	
	if (!feof(fp))
	{
		fclose(fp);
		return Not_to_End;
	}
	
	fclose(fp);
	return All_Correct;
	
	
}
