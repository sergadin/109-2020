#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "back.h"

int main(void) {
	int n = 3, i, j, k, corr;
	FILE *input;
	double **matr, **newmatr;
    double eps = 0.0001;
	input = fopen("input.txt", "r");
		matr = malloc(n * sizeof(double *));
		newmatr = malloc(n * sizeof(double *));
		for(j = 0; j < n; j++) {
			matr[j] = malloc(n * sizeof(double));
			newmatr[j] = malloc(n * sizeof(double));
		}
		for(j = 0; j < n; j++)
			for(i = 0; i < n; i++)
				fscanf(input, "%lf", &matr[j][i]);
		corr = back(matr, newmatr, n, eps);
        if(corr == 1) {
	        for(j = 0; j < n; j++)	{
		        for(k = 0; k < n; k++) {
			        printf("%lf ", newmatr[k][j]);
				}
                printf("\n");
		    }
        }	
        else
            printf("Sorry\n");
		for(j = 0; j < n; j++) {
			free(matr[j]);
			free(newmatr[j]);
		}
		free(matr);
		free(newmatr);
	fclose(input);
	return 0;
}
