#include "gauss.h"
#define input "input.txt"



int main(void)
{
    printf("i want very nice system of linear equentions\n");
    printf("which has only one solution\n");
    printf("thx for understanding\n");
    int n;
    FILE *file;
    if ((file = fopen(input, "r")) == NULL)
    {
	printf("cannot open file\n");
        return 0;
    }
    if ((fscanf(file, "%d", &n) != 1) || (n <= 0))
    {
	printf("cannot read size\n");
	fclose(file);
	return 0;
    } 

    double *a = malloc(sizeof(double *) * (n*(n+1)));
    double *x = malloc(sizeof(double *) * n);

    if ((a == NULL) || (x == NULL))
    {
	printf("smth wrong with memory\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
	for (int j = 0; j < n + 1; j++)
	{
	    if (fscanf(file, "%lf", &a[i*(n + 1) + j]) != 1)
            {
	        printf("cannot read array\n");
	        free(a);
	        free(x);
	        fclose(file);
	        return 0;
	    }
	}
    }

   
    printMatrix(n, a);
    printf("\n");
    find_answer(n, a, x);
 
    free(a);
    free(x);
    fclose(file);
    return 0;
}