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

void ERROR_RE(ErrorCode ret) {
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