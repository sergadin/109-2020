
#include "f.h"

int main() {
	int n = 4, m = 2*n, res, i,j, t,  err = SUCCESS;
	double *a, eps = 1e-16;
	FILE *fp;
	if (!(a = (double *)malloc(sizeof(double) * n * m) )) {
		printf("Not enough memory\n");
		return -1;
	}
	if (!(fp = fopen("a.txt","r")) ){
		err = ERROR_OPEN;
	}
	else
	{
		for (i = 0; i < n; ++i)
		{
			for(j = 0; j < m; j++)
			{				
				if(j > n - 1)
				{
					if(i == j)
						t = 1;
					else
						t = 0;
					a[i*m + j] = t;
				}
				else
				{
					if((fscanf(fp, "%lf", &a[i*m + j]) != 1))
					{
						fclose(fp);
						err = ERROR_READ;
						break;
					}
				}
			}
		}
		fclose(fp);
	}
	if (err != SUCCESS) {
		ERROR_RE(err);
		free(a);
		return -1; 
	}
	//printf("Данная матрица:\n");
	//print_matrix(a, n, m);
	res = matr(a, n, m, eps);
	if(res == 0)
	{
		printf("У матрицы нет обратной");
	}
	else
	{
		print_matrix(a, n, m);
	}
	//printf("Полученная матрица:\n");//
	//print_matrix(a, n, m);//
	printf("Rank = %d\n", res);
	free(a);
	return 0;
}