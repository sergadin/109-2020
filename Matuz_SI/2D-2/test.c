#include <stdio.h>
#include <stdlib.h>
#include "determinant.h"

#define input "input.txt"

int main(void)
{
    int size;
    int determinant = 0;
    int **matrix;
    FILE *file;
    if ((file = fopen(input, "r")) == NULL)
    {
	printf("cannot open file\n");
        return -1;
    }
    if ((fscanf(file, "%d", &size) != 1) || (size <= 0))
    {
	printf("cannot read size\n");
	fclose(file);
	return -1;
    } 
    matrix = (int **)malloc(size*sizeof(int*));
    if (matrix == NULL)
    {
	printf("smth wrong with memory\n");
        fclose(file);
        return -1;
    }
    for (int k = 0; k < size; k++)
    {
	if ((matrix[k] = (int *)malloc(size*sizeof(int))) == NULL)
	{
	    printf("smth wrong with memory\n");
            for(int j = 0; j < k-1; j++)
            {
                free(matrix[j]);
            }
            free(matrix);
	    fclose(file);
	    return -1;
	}	
    }

    for (int i = 0; i < size; i++)
    {
	for (int j = 0; j < size; j++)
	{
	    if (fscanf(file, "%d", &matrix[i][j]) != 1)
            {
	        printf("cannot read array\n");
	        for(int k = 0; k < size; k++)
                {
                    free(matrix[k]);
                }
                free(matrix);
	        fclose(file);
	        return -1;
	    }
	}
    }


    determinant = find_Det(matrix, size);
    printf("%d\n", determinant);


    fclose(file);
    for (int k = 0; k < size; k++)
    {
        free(matrix[k]);
    }
    free(matrix);
    return 0;
}