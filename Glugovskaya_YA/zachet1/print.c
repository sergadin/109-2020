#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "print.h"
#define MAX_PRN 20

void print(char **a, int n, int m)
{
	int N = (n > MAX_PRN ? MAX_PRN:n);
	int M = (m > MAX_PRN ? MAX_PRN:m);
	printf ("n %d m%d\n", N, M);
	
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%d %d %s", i, j, a[i*m + j]);
			if (j == M - 1) printf("\n");
		}
		if (i == N - 1)break;
	}
	
	printf("\n");
	return;	
}

void print_res(char **a, int n, int m, int MinI)
{
	int N = (n > MAX_PRN ? MAX_PRN:n);
	int M = (m > MAX_PRN ? MAX_PRN:m);
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			printf("%s%s ", a[MinI*m + j], a[i*m+j]);
			if (j == M - 1) printf("\n");
		}
		if (i == N - 1)break;
	}
}
	
int print_res_file(char **a, int n, int m, int MinI)
{
	FILE*fp;
	
	fp = fopen("result.txt","w");
	if (!fp) return Open_Err;
	
	int N = (n > MAX_PRN ? MAX_PRN:n);
	int M = (m > MAX_PRN ? MAX_PRN:m);
	
	printf("MinI: %d\n", MinI);
	
	for(int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			int LenEl = strlen(a[i*m + j]);
			int LenMin = strlen(a[MinI*m +j]);
			
			if (i == N - 1 & j == M - 1)
			{
				for (int k = 0; k < LenEl;  k++)
				fprintf(fp, "%c", a[i*m+j][k]);
			}
		
			else 
			{
				for (int k = 0; k < LenEl - 2;  k++)
				fprintf(fp, "%c", a[i*m+j][k]);
			}
			for (int k = 0; k < LenMin;  k++)
				fprintf(fp, "%c", a[MinI*m+j][k]);
			if (j == M - 1) fprintf(fp, "\n");
		}
		if (i == N - 1)break;
	}
	fclose(fp);
	return All_Correct;
}	