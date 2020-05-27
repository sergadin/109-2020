#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_matrix(FILE *file, char ***A, int N, int M)
{
	int i, j;
	size_t bufsize = 32;
	int error = 0;


	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
		{
			A[i][j] = NULL;
			if(getline(&A[i][j],&bufsize,file) == -1)
			{
				fprintf(stderr,"Input file format is bad\n");
				error = -1;
			}
		}
	}

	return error;
}

int strings_lexic_compare(char **a, char **b, int m)
{
	int j1 = 0, k1 = 0, j2 = 0, k2 = 0;

	while(1)
	{
		//находим первый символ в верхней строке
		while(a[j1][k1] == 10)
		{
			if(k1>=strlen(a[j1]) - 1)
			{
				j1++;
				k1 = 0;
			}
			else
				k1++;

			if(j1 >= m)
				break;
		}
		//находим первый символ в нижней строке
		while(b[j2][k2] == 10)
		{
			if(k2>=strlen(b[j2]) - 1)
			{
				j2++;
				k2 = 0;
			}
			else
				k2++;

			if(j2 >= m)
				break;
		}

		if(j1 >= m && j2 < m)
			return -1;
		
		if(j1 < m && j2 >= m)
			return 1;

		if(j1 >= m && j2 >= m)
			return 0;
		
		if(a[j1][k1] < b[j2][k2])
			return -1;

		if(a[j1][k1] > b[j2][k2])
			return 1;

		if(a[j1][k1] == b[j2][k2])
		{
			if(k1>=strlen(a[j1]) - 1)
			{
				j1++;
				k1 = 0;
			}
			else
				k1++;
			if(j1 >= m)
				return 0;

			if(k2>=strlen(b[j2]) - 1)
			{
				j2++;
				k2 = 0;
			}
			else
				k2++;
			if(j2 >= m)
				return 0;

		}
	}
}

int main(int argc, char *argv[])
{
	int n,m;
	char ***A;
	FILE *input;
	int i, j;
	long int k;
	int imin = 0;
	int len;
	FILE *output;
	char *B;

	if(argc != 2)
	{
		fprintf(stderr,"few arguments\n");
		return -1;
	}

	if((input = fopen(argv[1],"r")) == NULL)
	{
		fprintf(stderr,"Input file opening error\n");
		return -1;
	}
	if(fscanf(input,"%d %d\n",&n,&m) != 2)
	{
		fprintf(stderr,"Input file format is bad\n");
		fclose(input);
		return -1;
	}
	A = malloc(n*sizeof(char**));
	for(i = 0; i < n; i++)
		A[i] = malloc(m*sizeof(char *));
	
	if(read_matrix(input, A, n, m) != 0)
	{
		fprintf(stderr,"Matrix reading error\n");
		fclose(input);

		return -1;
	}

	for(i = 0; i < n; i++)
	{
		if(strings_lexic_compare(A[i],A[imin],m) < 0)
			imin = i;
	}


	for(i = 0; i < n; i++)
	{
		if(i != imin)
		{
			for(j = 0; j < m; j++)
			{
				B = malloc(strlen(A[i][j]) * sizeof(char));
				for(k = 0; k < strlen(A[i][j]);k++)
					B[k] = A[i][j][k];

				len = strlen(A[i][j]);
				A[i][j] = realloc(A[i][j], len + strlen(A[imin][j]) - 1);

				for(k = len - 1; k >=0; k--)
				{
					A[i][j][k+strlen(A[imin][j])-1] = B[k];
				}
				A[i][j][len+strlen(A[imin][j])-2] = 0;
				for(k = 0; k < strlen(A[imin][j]) - 1; k++)
				{
					A[i][j][k] = A[imin][j][k];
				}

				free(B);
			}
		}
	}
	fclose(input);

	if((output = fopen("result.txt","w")) == NULL)
	{
		fprintf(stderr, "output file opening error\n");
		return -1;
	}

	fprintf(output,"%d %d\n",n,m);
	for(i = 0 ; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			fprintf(output,"%s",A[i][j]);
		}
	}
	fclose(output);

	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)
		{
			free(A[i][j]);
		}
		free(A[i]);
	}
       	free(A);
	return 0;
}	
