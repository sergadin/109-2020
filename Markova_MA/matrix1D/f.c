#include "typedef.h"


/*void print_matrix(double *a, int n, int m) {
	int i, j;
	for (i = 0; i < n; ++i) {
		for (j = 0; j < m; ++j)
			printf("%10.3e ", a[i*m + j]);
		printf("\n");
	}
	printf("\n");
}*/

void ERROR_RE(int ret) {
	switch (ret)
	{
		case ERROR_OPEN:
			printf("Cannot open %s\n");
		case ERROR_READ:
			printf("Cannot read %s\n");
		default:
			printf("Unknown error %d in file %s\n");
	}
}

void ved_null(double *a, int n, int m, int ii, int jj, double max) {
	int i;
	double ved = a[jj * m + ii];
	for(i = ii + 1; i < m; ++i)
		a[jj*m + i] -= (a[ii*m +i] / max) * ved;
}

void change_column(double *a, int n, int m, int i, int j) {
	int k; double tmp;
	for(k = 0; k < n; ++k) {
		tmp = a[k*m + i]; 
		a[k*m + i] = a[k*m + j]; 
		a[k*m + j] = tmp;
	}
}

int rank(double *a, int n, int m) {
	int i, j, pos, res = n;
	double max, help;
	for(i = 0; i < n - 1; ++i) {
		for(pos = i, max = fabs(a[i*m + i]), j = i + 1; j < m; ++j) {
			help = fabs(a[i*m + j]);
			if(max < help) {
				max = help;
				pos = j;
			}
		}
 		if(fabs(max) <= eps) {
			--res;
			continue;
 		}

		if(i != pos)
			change_column(a, n, m, i, pos);
		max = a[i*m + i];
		for(j = i + 1; j < n; ++j)
			ved_null(a, n, m, i, j, max);
	}
	if(fabs(a[i*m + i]) <= eps)
		--res;
	return res;
}
