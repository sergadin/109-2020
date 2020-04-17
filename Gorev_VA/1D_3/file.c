#include <stdio.h>
#include <stdlib.h>

#define eps 0.0000001

void PLUS1(double *matr, int n);
void PLUS1(double *matr, int n)
{
	matr[0] = 1;
}

int main(void)
{
	double *matr;
	int N = 2;

	matr = (double*)malloc(N * N * sizeof(double));
	matr[0] = 0, matr[1] = 1, matr[2] = 2, matr[3] = 3;
	
	PLUS1(matr, N);
	
	printf("%g\n", matr[0]);

	free(matr);
	return 0;
}
