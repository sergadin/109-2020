#include <stdio.h>
#include <stdlib.h>
#include "read_matr.h"
#define Open_Err -1
#define Read_Err -2
#define Not_to_End -3
#define All_Correct 1


int read_matr(double *a, int n, char *name)
{
	FILE*fp;
	int i=0;
	
	fp = fopen(name,"r");
	if (!fp) return Open_Err;
	
	for (i = 0; i < n*n; i++)
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
	
	fclose(fp);
	return All_Correct;
	
	
}
