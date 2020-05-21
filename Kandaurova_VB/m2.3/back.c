#include <stdio.h>
#include "back.h"
#include <math.h>

int obr(double **matrix, double **newmatr, double **matr, int n, double eps) {
    int k, j, i, t;
	double c;
    //double **matr;
    //matr = malloc(n * sizeof(double *));
    for(j = 0; j < n; j++) 
	    matr[j] = malloc(n * sizeof(double));
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            matr[i][j] = matrix[i][j];
            if(i == j)
                newmatr[i][j] = 1;
            else
                newmatr[i][j] = 0;
        }
    }
    for(j = 0; j < n; j++) {
            for(i = j; i < n; i++) {
                k = -1;
                if(fabs(matr[i][j]) > eps) {
                    k = i;
                    break;  
                }         
            }
            if(k == -1)
                return 0;
            if(k != i) {
                for(i = 0; i < n; i++) {
                    matr[j][i] += matr[k][i];
                    newmatr[j][i] += newmatr[k][i];      
                }
            }
            for(i = j + 1; i < n; i++) {
                //c = matr[i][j] / matr[j][j];
                if(fabs(matr[j][j]) > eps) {
                    c = matr[i][j] / matr[j][j];
                    for( t = j; t < n; t++) {
                        matr[i][t] -= matr[j][t] * c;
                        newmatr[i][t] -= newmatr[j][t] * c;
                    }
                }            
            }   
    }
    for(i = n - 2; i >= 0; i--) {
        for(j = n - 1; j > i; j--) {
            if(fabs(matr[j][j]) > eps) {
                for(k = 0; k < n; k++) {
                    c = matr[i][j] / matr[j][j];
                    matr[i][k] -= matr[j][k] * c; 
                    newmatr[i][k] -= newmatr[j][k] * c; 
                }
            }
        }
    }
/*for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%lf ", matr[i][j]);
        }
        printf("\n");
    }*/
   for(i = 0; i < n; i++) {
        c = matr[i][i];
        if(fabs(c) > eps) {
            for(j = 0; j < n; j++) {
                matr[i][j] /= c;
                newmatr[i][j] /= c;
            }
        } 
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
    //for(j = 0; j < n; j++) {
		//	free(matr[j]);
		//}
	//	free(matr);
    return 1;
}
