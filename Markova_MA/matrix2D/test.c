
#include "f.h"

int main() {
	int n = 4, m = 2*n, res, i,j, t,  err = SUCCESS;
	double *a, eps = 1e-16;
	FILE *fp;
	if (!(a = (double *)malloc(sizeof(double) * n * m) )) {
		printf("Not enough memory\n");
		return 0;
	}
	if (!(fp = fopen("a.txt","r")) ){
		err = ERROR_OPEN;
	}
	else
	{
		for (i = 0; i < n; ++i)
		{
			for(j = 0; j < n; j++)
			{			
				if((fscanf(fp, "%lf", &a[i*m + j]) != 1))
				{
					printf("%d\n %d\n", i, j);
					fclose(fp);
					err = ERROR_READ;
					break;
				}
			}
			for(j = n; j < m; j++)
			{
				if(i == (j - n))
					t = 1;
				else
					t = 0;
				a[i*m + j] = t;
			}
		}
		fclose(fp);
	}
	if (err != SUCCESS) {
		ERROR_RE(err);
		free(a);
		return 0; 
	}
	//printf("Данная матрица:\n");
	//print_matrix(a, n, m);
	res = matr(a, n, m, eps);
	if(res == 0)
	{
		printf("puk");
	}
	else
	{
		print_matrix(a, n, m);
	}
	//printf("Полученная матрица:\n");//
	//print_matrix(a, n, m);//
	\\\printf("Rank = %d\n", res);
	free(a);
	return 0;
}