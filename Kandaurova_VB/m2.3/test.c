#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "back.h"

int main(void) {
	int n = 3, i, j, k, corr;
	FILE *input;
	double **matr, **newmatr, **matrix;
    double eps = 0.0001, ans;
	input = fopen("input.txt", "r");
		matr = malloc(n * sizeof(double *));
		newmatr = malloc(n * sizeof(double *));
        matrix = malloc(n * sizeof(double *));
		for(j = 0; j < n; j++) {
			matr[j] = malloc(n * sizeof(double));
            matrix[j] = malloc(n * sizeof(double));
			newmatr[j] = malloc(n * sizeof(double));
		}
		for(j = 0; j < n; j++)
			for(i = 0; i < n; i++)
				fscanf(input, "%lf", &matr[j][i]);
		corr = obr(matr, newmatr, matrix, n, eps);
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
        for(j = 0; j < n; j++)	{
		        for(k = 0; k < n; k++) {
			        printf("%lf ", matr[k][j]);
				}
                printf("\n");
		    }
        corr = 1;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                ans = 0;
                for(k = 0; k < n; k++)
                       ans += matr[i][k] * newmatr[k][j]; 
                       //if((i == 0) && (j == 2))
                          // printf("%lf\n", matr[i][k] * newmatr[k][j]);
                               printf("%lf\n", newmatr[k][j]);
                //printf("%d %d %lf\n", i, j, ans);           
                if((i == j) && (fabs(ans - 1) > eps)) {
                    corr = 0;
                    printf("%d %d %lf\n", i, j, ans);
                    break;
                } 
                if((i != j) && (fabs(ans) > eps)) {
                    corr = 0;
                    printf("%d %d %lf\n", i, j, ans);
                    break;
                }                  
            }
        }
        if(corr == 1)
            printf("ok\n");
        else 
            printf("Answer is not true:(\n");
		for(j = 0; j < n; j++) {
			free(matr[j]);
			free(newmatr[j]);
            free(matrix[j]);
		}
		free(matr);
		free(newmatr);
        free(matrix);
	fclose(input);
	return 0;
}
