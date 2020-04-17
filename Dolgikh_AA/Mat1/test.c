#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "math.h"

int main(void)
{
	FILE *input;
	int n_rows, n_cols, ans, trueans, i, j;
	double *data;

	if((input = fopen("input.txt","r")) == NULL)
	{
		fprintf(stderr, "File opening error\n");
		free(data);
		return -1;
	}

	for(i = 0; i < 5; i++)
	{
		fprintf(stdout, "Test #%d\n", i+1);
		if(fscanf(input, "%d %d", &n_rows, &n_cols) != 2)
		{
			fprintf(stderr, "Wrong input\n");
			return -1;
		}
		if((data = (double *)malloc(n_rows * n_cols * sizeof(double))) == NULL)
		{
			fprintf(stderr, "Memory error\n");
			fclose(input);
			return -1;
		}
		for(j = 0; j < n_rows * n_cols; j++)
		{
			if(fscanf(input, "%lf", &data[j]) != 1)
			{
				fprintf(stderr, "Wrong input\n");
				fclose(input);
				free(data);
				return -1;
			}
		}
		if(fscanf(input, "%d", &trueans) != 1)
		{
			fprintf(stderr, "Wrong input\n");
			fclose(input);
			free(data);
			return -1;
		}

		ans = rank(data, n_rows, n_cols);
		fprintf(stdout, "Rank is %d. ", ans);
		if(ans != trueans)
		{
			fprintf(stdout, "Wrong answer :(\n");
		}
		else
			fprintf(stdout, "Correct answer :)\n");
		
		free(data);
	}	

	fclose(input);


	return 0;
}
