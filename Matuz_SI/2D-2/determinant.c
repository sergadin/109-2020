#include <stdlib.h>
#include "determinant.h"

int find_Det(int **matrix, int size)
{
    int det = 0;
    int degree = 1; 

    if(size == 1) 
    {
        return matrix[0][0];
    }

    else if(size == 2) 
    {
        return (matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]);
    }
    else 
    {
        int **newMatrix = (int**)malloc((size-1)*sizeof(int*));
        for(int i = 0; i < size-1; i++) 
        {
            newMatrix[i] = (int*)malloc((size-1)*sizeof(int));
        }
        for(int j = 0; j < size; j++) 
        {
            MinorRowCol(matrix, size, 0, j, newMatrix);

            det += (degree * matrix[0][j] * find_Det(newMatrix, size-1));
            degree *= -1;;
        }

        for(int i = 0; i < size-1; i++) 
        {
            free(newMatrix[i]);
        }
        free(newMatrix);
    }

    return det;
}


void MinorRowCol(int **matrix, int size, int row, int col, int **newMatrix) 
{
    int deltaRow = 0; 
    int deltaCol = 0; 
    for(int i = 0; i < size-1; i++) 
    {
        if(i == row) 
        {
            deltaRow = 1; 
        }
        deltaCol = 0; 
        for(int j = 0; j < size-1; j++) 
        {
            if(j == col) 
            {
                deltaCol = 1;
            }
            newMatrix[i][j] = matrix[i + deltaRow][j + deltaCol];
        }
    }
    return;
}



