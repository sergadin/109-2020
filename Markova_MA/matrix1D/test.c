
#include "f.h"

int main() {
	int n, m, res, i,  err = SUCCESS;
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
		for (i = 0; i < m * n; ++i)
		{
			if (fscanf(fp, "%lf", &a[i]) != 1) {
				fclose(fp);
				err = ERROR_READ;
				break;
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
	res = rank(a, n, m, eps);
	//printf("Полученная матрица:\n");//
	//print_matrix(a, n, m);//
	printf("Rank = %d\n", res);
	free(a);
	return 0;
}