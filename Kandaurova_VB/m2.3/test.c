#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "back.h"

int main(void) {
	int n = 3, i, j, k, corr, flag;
	FILE *input;
	double **matrix, **newmatr;
    double eps = 0.0001, ans;
	input = fopen("input.txt", "r");
        if((matrix = malloc(n * sizeof(double *))) == NULL)
            return 0;
		for(j = 0; j < n; j++) {
            if((matrix[j] = malloc(n * sizeof(double))) == NULL)
                return 0;
		}
		for(j = 0; j < n; j++)
			for(i = 0; i < n; i++)
				fscanf(input, "%lf", &matrix[j][i]);
		newmatr = obr(matrix, n, eps, &flag);
        if(flag == 1) {
	        for(j = 0; j < n; j++)	{
		        for(k = 0; k < n; k++) {
			        printf("%lf ", newmatr[k][j]);
				}
                printf("\n");
		    }
        }	
        else
            printf("Sorry\n");
        corr = 1;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                ans = 0;
                for(k = 0; k < n; k++) 
                       ans += matrix[i][k] * newmatr[k][j];            
                if((i == j) && (fabs(ans - 1) > eps)) {
                    corr = 0;
                } 
                if((i != j) && (fabs(ans) > eps)) {
                    corr = 0;
                }                  
            }
        }
        if(corr == 1)
            printf("ok\n");
        else 
            printf("Answer is not true:(\n");
		for(j = 0; j < n; j++) {
			free(newmatr[j]);
            free(matrix[j]);
		}
		free(newmatr);
        free(matrix);
	fclose(input);
	return 0;
}
