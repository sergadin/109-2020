#include <stdio.h>
#include "back.h"
#include <math.h>

int back(double **matr, double **newmatr, int n, double eps) {
    int k, j, i;
	double c;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            if(i == j)
                newmatr[i][j] = 1;
            else
                newmatr[i][j] = 0;
        }
    }
    for(j = 0; j < n; j++) {
            for(i = j; i < n; i++) {
                k = -1;
                if(fabs(matr[i][j]) > 0) {
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
                c = matr[i][j] / matr[j][j];
                if(fabs(matr[j][j]) > eps) {
                    for(int t = j; t < n; t++) {
                        matr[i][t] -= matr[j][t] * c;
                        newmatr[i][t] -= newmatr[j][t] * matr[i][j] / matr[j][j];
                    }
                }            
            }   
    }
    for(i = 0; i < n; i++) {
        c = matr[i][i];
        for(j = i; j < n; j++) {
            matr[i][j] /= c;
            newmatr[i][j] /= c;
        } 
    }
    for(j = 1; j < n; j++) {
        for(i = 0; i < j; i++) {
            if(matr[i][j] != 0) {
                matr[i][j] -= matr[i][i] * matr[i][j]; 
                newmatr[i][j] -= newmatr[i][i] * matr[i][j]; 
            }
        }
    }
    /*for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            printf("%lf ", matr[i][j]);
        }
        printf("\n");
    }*/
    return 1;
}
