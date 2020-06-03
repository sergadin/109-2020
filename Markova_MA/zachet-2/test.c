
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main() {
	int n, m, i, j, pos_j = -1, pos_i = -1, sum = 0;
	double *a, max = 0;
	FILE *inp, *outp;
	if (!(inp = fopen("input.txt","r")) )
	{
		printf("ERROR\n");
		return -1;
	}
	if ((outp = fopen("output.txt", "w")) == NULL) 
	{
        printf("ERROR\n");
        fclose(inp);
        return -1;
    }
	if (fscanf(inp, "%d", &n) != 1 || fscanf(inp, "%d", &m) != 1) {
		fclose(inp);
		//err = ERROR_READ;
		return -1;
		//break;
	}
	if (!(a = (double *)malloc(sizeof(double) * n * m) )) {
		printf("Not enough memory\n");
		fclose(inp);
		fclose(outp);
		return -1;
	}
	else
	{
		for (i = 0; i < m * n; ++i)
		{
			if (fscanf(inp, "%lf", &a[i]) != 1) {
				fclose(inp);
				//err = ERROR_READ;
				fclose(inp);
				fclose(outp);
				free(a);
				return -1;
			}
		}
		fclose(inp);
	}
	/*if (err != SUCCESS) {
		ERROR_RE(err);
		free(a);
		return -1; 
	}*/
	printf("kyky\n");
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			sum += a[i*m + j];
		}
		sum /= m;
		max = sum;
		for(j = 0; j < m; j++)
		{
			if(a[i*m + j] > max)
			{
				if(pos_j == -1 || pos_j < j)
				{	
					pos_j = j;
					pos_i = i;
				}
			}
		}
	}
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			if(i == pos_i)
				fprintf(outp, "%lf ",a[i*m+j]);
			else
			{
				if(a[i*m + j] > a[pos_i*m + j])
					fprintf(outp, "%lf ",a[i*m+j]);
				else
					fprintf(outp, "%lf ",a[pos_i*m + pos_j]);
			}
		}
		fprintf(outp, "\n");
	}
	//printf("Данная матрица:\n");
	//print_matrix(a, n, m);
	//res = rank(a, n, m, eps);
	//printf("Полученная матрица:\n");//
	//print_matrix(a, n, m);//
	//printf("Rank = %d\n", res);
	free(a);
	fclose(outp);
	return 0;
}