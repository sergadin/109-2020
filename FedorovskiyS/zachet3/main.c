#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum Err
{
	SUCCESS,
	ERROR_OPEN,
	ERROR_READ,
	ERROR_NOT_ENOUGH_DATA
};

void task(double *arr, int rows, int columns);
void swap_columns (double *arr, int rows, int columns, int c1, int c2);

void swap_columns (double *arr, int rows, int columns, int c1, int c2)
{
	int i, j;
	double tmp;
	//Перестановка двух столбцов.
	for (i = 0; i < rows; i++)
	{
		tmp = arr[i*columns + c1];
		arr[i*columns + c1] = arr[i*columns + c2];
		arr[i*columns + c2] = tmp;
	}
}

void task (double *arr, int rows, int columns)
{
	int i, j, row_index = 0, min_index, is_find = 0;
	double mult, sum, max_mult, prev_max_mult;
	double min_el;
	//Выбор строки где произведение эл-тов строки максимально и больше суммы. 
    
    mult = 1.0;
    sum = 0.0;
    for (j = 0; j < columns; j++)
    {
        sum += arr[j]/columns;
        mult *= arr[j];
    }
    
    if (mult > sum)
    {
        is_find = 1;
        prev_max_mult = mult;
    }
    
    
	for (i = 0; i < rows; i++)
	{
		mult = 1.0;
		sum = 0.0;
		for (j = 0; j < columns; j++)
		{
			sum += arr[i*columns + j]/columns;
			mult *= arr[i*columns + j];
		}
		max_mult = mult;
        
        if (!is_find && (mult > sum))
        {   
            is_find = 1;
            prev_max_mult = mult;
        }
        
		if ((mult > sum) && (max_mult > prev_max_mult))
		{
			prev_max_mult = max_mult;
			row_index = i;
		}
	}
	
	if (is_find)
    {
        //Переставить столбцы так, чтобы элементы найденной строки неубывали.
        for (i = 0; i < columns; i++)
        {
            min_el = arr[row_index*columns + i];
            min_index = i;
            //Ищем минимальный в оставшейся части строки.
            for (j = i; j < columns; j++)
            {
                if (min_el > arr[row_index*columns + j])
                {
                    min_el = arr[row_index*columns + j];
                    min_index = j;
                }
            }
            //Переставляем столбцы.
            swap_columns (arr, rows, columns, i, min_index);
        }
    }
}

int main(void){
    int rows, columns, i, j;
    double* matrix;
    FILE *fp;
    fp = fopen("input.txt", "r");
    if(!fp)
        return ERROR_OPEN;
    if(fscanf(fp, "%d%d", &rows, &columns) != 2){
        fclose (fp);
        return ERROR_READ;
    }
    matrix = (double*)malloc(rows*columns*sizeof(double));
    if(!matrix){
        fclose(fp);
        return ERROR_NOT_ENOUGH_DATA;
    }
    for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			if (fscanf(fp, "%lf", matrix + j*columns + i) != 1)
			{
				fclose (fp);
                free(matrix);
				return ERROR_READ;
			}
		}
	}
	fclose (fp);
    task(matrix, rows, columns);
    fp = fopen("output.txt", "w");
    if(!fp){
        free(matrix);
        return ERROR_OPEN;
    }
    fprintf(fp, "%d %d\n", rows, columns);
    for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			fprintf(fp, "%lf ", matrix[i*columns + j]);
		}
		fprintf(fp, "\n");
	}
	free(matrix);
    fclose(fp);
	return SUCCESS;
}
