#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"prn_matr.h"
#include"solve.h"
#define Mem_Err -4
// Открываем файл, считаваем m и n и матрицу соответствующей размерности


//1.exe matr.txt
int main(int argc,char **argv)
{
	FILE*fp;
	int n, m;
	double t, res;
	char *File_Name = 0;
	double *a;
	
	if (argc != 2)
	{ 
		printf("Usage:%s filename\n", argv[0]);
		return 1;
	}
	File_Name = argv[1];
	fp = fopen(File_Name,"r");
	
	if (!fp) return -1;
	
	fscanf(fp, "%d %d\n", &n, &m);
	printf("%d %d\n", n, m);
	
	if (!(a = (double*) malloc (n*m*sizeof(double))))
	{
		printf("not enough memory\n");
		return Mem_Err;
	}
	for (int i = 0; i < n*m; i++)
	{
		if (fscanf(fp,"%lf", &a[i])!=1)
		{
			fclose(fp);
			return -1;
		}
	}
	fclose(fp);
	
	printf("Matrix A:\n");
	prn_matr(a, n, m);

	solve(a, n, m);
	prn_matr(a, n, m);

	free(a);

	return 0;
}