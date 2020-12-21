#include <stdio.h>
#include <stdlib.h>
void function(int *A, int *B, int n, int m, FILE *fout);
int compare(const void *x1, const void *x2);

int main(void)
{
	FILE *fin1, *fin2, *fout;
	int n, m;
	int *A, *B;
	if ((fin1 = fopen("input1.txt", "r")) == NULL)
	{
		return -1;
	}
	if ((fin2 = fopen("input2.txt", "r")) == NULL)
	{
		fclose(fin1);
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		fclose(fin1);
		fclose(fin2);
	}
	if ((fscanf(fin1, "%d", &n) != 1) || (fscanf(fin2, "%d", &m) != 1))
	{
		fclose(fin1);
		fclose(fin2);
		fclose(fout);
		return -1;
	}
	if ((n < 1) || (m < 1))
	{
		fclose(fin1);
		fclose(fin2);
		fclose(fout);
		return -1;
	}
	if ((A = (int*)malloc(n * sizeof(int))) == NULL) 
	{
		fclose(fin1);
		fclose(fin2);
		fclose(fout);
		return -1;
	}
	if ((B = (int*)malloc(m * sizeof(int))) == NULL)
	{
		fclose(fin1);
		fclose(fin2);
		fclose(fout);
		free(A);
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		if(fscanf(fin1, "%d", &A[i]) != 1)
		{
			fclose(fin1);
			fclose(fin2);
			fclose(fout);
			free(A);
			free(B);
			return -1;
		}
	}
	fclose(fin1);
	for (int i = 0; i < m; i++)
	{
		if(fscanf(fin2, "%d", &B[i]) != 1)
		{
			fclose(fin2);
			fclose(fout);
			free(A);
			free(B);
			return -1;
		}
	}
	fclose(fin2);
	function(A, B, n, m, fout);
	fclose(fout);
	free(A);
	free(B);
	return 0;

}

void function(int *A, int *B, int n, int m, FILE *fout)
{
	int key = 0;
	printf ("\n");
	qsort(A, n, sizeof(int), compare); 
	for(int i = 0; i < n - 1; i++)
	{
		if (A[i] == A[i + 1])
		{
			for (int j = i + 1; j < n; j++)
			{
				A[j - 1] = A[j];
			}
			n--;
			i--;
		}
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if (key == 1)
			{
				break;
			}
			if (A[i] == B[j])
			{
				key = 1;
			}

		}
		if (key == 0)
		{
			fprintf(fout, "%d ", A[i]);
		}
		key = 0;
	}
}

int compare(const void *x1, const void *x2)
{
	return (*(int*)x1 - *(int*)x2);
}
