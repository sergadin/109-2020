#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "solve.h"
#include "MaxEl.h"
#include "prn_matr.h"

int Inverse_matrix(double *a, int n)
{
	double *MINORS;
	if (!(MINORS = (double*) malloc (n*n*sizeof(double))))
	{
		printf("not enough memory\n");
		return Err_of_Mem;
	}

	Find_Matr_Dopolneni(a, MINORS, n);
	TRANS(MINORS, n);
	double det = DET(a, n);
	printf("Det: %lf\n", det);
	
	printf("Matrix A^(-1):\n");
	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%lf ", MINORS[i * n + j]/det);
			if (j == n - 1) printf("\n");
		}
		if (i == n - 1)break;
	}
	
	free(MINORS);
	return 1;
}
	

double DET(double *a, int n){
	
	int i, j, l, sgn = 1;;
	double del, kof, det = 1;
	
	for (i = 0; i < n; i++)
	{		
		if (i < n - 1) sgn *= Raising_row_with_MaxEl_In_Collon(a, n, i);
		
		if (fabs(a[i * n + i]) > EPS)
		{
			
			del = a[i * n  + i];
		
			for (j = i + 1; j < n; j++)
			{
				kof = a[j * n + i] / del;
			
				for (l = 0; l < n ; l++)
				{
					a[j * n + l] -= kof * a[i * n + l];		
				}
			}
		}
		det *= a[i * n + i];
	}
	return det * sgn;
}
void Find_Matr_Dopolneni(double *a, double *MINORS, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			MINORS[i*n + j] = pow(-1, i+j)*DET_MINOR(a, i, j, n);
		}
	}
}

double DET_MINOR(double *a, int I, int J, int n)
{
	int i, j;
	double *buf, Det_Minor; 
	buf = (double*) malloc (n*n*sizeof(double));
	for (i = 0; i < I; i++)
	{
		for (j = 0; j < J; j++)
		{
			buf[i * (n - 1) + j] = a[i * n + j];
		}
		for (j = J+1; j < n; j++)
		{
			buf[i * (n - 1) + j - 1] = a[i * n + j];
		}
	}
	for (i = I+1; i < n; i++)
	{
		for (j = 0; j < J; j++)
		{
			buf[(i-1) * (n - 1) + j] = a[i * n + j];
		}
		for (j = J+1; j < n; j++)
		{
			buf[(i-1) * (n - 1) + j - 1] = a[i * n + j];
		}
	}
	//printf("Matr without %d %d\n", I, J);
	//prn_matr(buf, n-1);
	Det_Minor = DET(buf, n-1);
	free(buf);
	return Det_Minor;
}

void TRANS(double *MINORS, int n)
{
	int i, j;
	double buf;
	for (i=0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			buf = MINORS[i * n + j];
            MINORS[i * n + j] = MINORS[j * n +i];
            MINORS[j * n + i] = buf;
		}
	}
}