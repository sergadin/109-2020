#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
FILE *inp;
int n_rows, n_cols, i, j, row;
double *data;

inp = fopen("input.txt", "r");

if (inp == NULL)
    {
    fclose(inp);
    free(data);
    fprintf(stderr, "input err\n");
    return -1;
    }

for(i = 0; i < 3; i++)
	{
		fprintf(stdout, "\n Test %d\n", i+1);
		if(fscanf(inp, "%d %d", &n_rows, &n_cols) != 2)
		{
			fprintf(stderr, "Wrong input\n");
			return -1;
		}
		if((data = (double *)malloc(n_rows * n_cols * sizeof(double))) == NULL)
		{
			fprintf(stderr, "Memory error\n");
			fclose(inp);
			return -1;
		}
    for(j = 0; j < n_rows * n_cols; j++)
	{
		if(fscanf(inp, "%lf", &data[j]) != 1)
		{
			fprintf(stderr, "Wrong input\n");
			fclose(inp);
			free(data);
			return -1;
		}
	}
	row = find_row(data, n_rows, n_cols);
    sort(data,n_rows, n_cols,row);
    printmat(data, n_rows, n_cols, row);
	fprintf(stdout,"\n");
		fprintf(stdout, "row is %d .\n ", row);
		free(data);
	}	

	fclose(inp);


	return 0;
}





