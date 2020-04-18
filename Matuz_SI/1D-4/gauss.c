#include "gauss.h"
#define EPS 0.000001



void copyMatrix(int n, const double *old_matrix, double *new_matrix)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            new_matrix[i*(n + 1) + j] = old_matrix[i*(n + 1) + j];
        }
    }
}


void printMatrix(int n, double *matrix){

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n + 1; j++)
        {
            printf("%lf\t", matrix[i*(n + 1) + j]);
        }
        printf("\n");
    }
}

void find_answer(int n, double *data, double *x)
{
    double *matrix = malloc(sizeof(double *) * n * (n+1));
    copyMatrix(n, data, matrix);

    for(int i = 0; i < n; i++)
    {
        //Partial Pivoting
        for(int k = i + 1; k < n; k++)
        {
            //printf("%lf %lf\n", fabs(matrix[i*(n + 1) + i]), fabs(matrix[k*(n + 1) + i]));
            if(fabs(matrix[i*(n + 1) + i]) < fabs(matrix[k*(n + 1) + i])){
                //Swap the rows
                for(int j = 0; j < n + 1; j++){
                    double temp;
                    temp = matrix[i*(n + 1) + j];
                    matrix[i*(n + 1) + j] = matrix[k*(n + 1) + j];
                    matrix[k*(n + 1) + j] = temp;
                }
            }
        }

        for (int k = i; k < n; k++) {
            double tmp = matrix[k*(n + 1) + i];
            if (fabs(tmp) < EPS) continue;
            for (int j = 0; j < n + 1; j++)
                matrix[k*(n + 1) + j] = matrix[k*(n + 1) + j] / tmp;
            if (i == k) continue;
            for (int j = 0; j < n + 1; j++)
                matrix[k*(n + 1) + j] -= matrix[i*(n + 1) + j];
        }
    }
    for (int k = n - 1; k >= 0; k--)
    {
        x[k] = matrix[k*(n + 1) + n];
        for (int j = 0; j < k; j++)
            matrix[j*(n + 1) + n] -= matrix[j*(n + 1) + k] * x[k];
    }
    printMatrix(n, matrix);
    for (int i = 0; i < n; i++)
    {
        printf("x[%d] = %lf\n", i+1, x[i]);
    }

    free(matrix);
}