#include <stdio.h>
#include <stdlib.h>
#include "prn_matr.h"
#define MAX_PRN 20

void prn_matr(double *a, int n)
{
	int i, j, N = (n > MAX_PRN ? MAX_PRN:n);
	
	for(i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%lf ", a[i*n + j]);
			if (j == N - 1) printf("\n");
		}
		if (i == N - 1)break;
	}
	
	printf("\n");
	return;	
}