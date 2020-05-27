#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _N 2

char *read_str(FILE *input)
{
	char *str;
	char buf[_N];
	int i = 0;
	int kN = 0;
	char c = 0;
	int Eof = 0;
	
	str = (char*)malloc(1 * sizeof(char));
	str[0] = 0;
	while (!Eof && (c != '\n'))
	{
		if (fscanf(input, "%c", &c) != 1)
		{
			Eof = 1;
			continue;
		}
		if ((c == '\r') || (c == '\n'))
			continue;
		buf[i] = c;
		i++;
		if (Eof || (i >= _N))
		{
			int j = 0;
			str = (char*)realloc(str, (kN + 1 + i) * sizeof(char));
			while (j < i)
			{
				str[kN + j] = buf[j];
				j++;
			}
			str[kN + i] = 0;
			kN += i;
			i = 0;
		}
	}
	if (i != 0)
	{
		int j = 0;
		str = (char*)realloc(str, (kN + 1 + i) * sizeof(char));
		while (j < i)
		{
			str[kN + j] = buf[j];
			j++;
		}
		str[kN + i] = 0;
		kN += i;
		i = 0;
	}
	return str;
}

char ***read_matr(FILE *input, int *m, int *n)
{
	int M, N;
	int i = 0, j = 0;
	char ***A;
	char *Q;
	fscanf(input, "%d", &M);
	fscanf(input, "%d", &N);
	A = (char***)malloc(M * sizeof(char**));
	i = 0;
	while (i < M)
		{
			A[i] = (char**)malloc(N * sizeof(char*));
			i++;
		}
	i = 0;
	Q = (char*)malloc(100 * sizeof(char));
	fgets(Q, 100, input);
	free(Q);
	while (i < M)
	{
		j = 0;
		while (j < N)
		{
			A[i][j] = read_str(input);
			//printf("%s", A[i][j]);
			j++;
		}
		i++;
	}
	*m = M, *n = N;
	return A;
}

int is_pal(char **str, int size_of_str);
int is_pal(char **str, int size_of_str)
{
	int i = 0;
	int j = 0;
	int i_glob = 0;
	int j_glob = 0;
	int i_str = 0;
	int j_str = 0;
	if (size_of_str == 0)
		return 1;
		
	while (i < size_of_str)
	{
		j_glob = j_glob + strlen(str[i]);
		i++;
	}
	if (j_glob == 0)
		return 1;
	
	i_glob = 0;
	j_glob--;
	i_str = 0;
	j_str = size_of_str - 1;
	while ((j_str > 0) && (strlen(str[j_str]) == 0))
		j_str--;
	i = 0;
	j = strlen(str[j_str]) - 1;
	while (i_glob < j_glob)
	{
		if (strlen(str[i_str]) == 0)
		{
			i_str++;
			continue;
		}
		if (strlen(str[j_str]) == 0)
		{
			j_str--;
			continue;
		}
		if (str[i_str][i] != str[j_str][j])
		{
			return 0;
		}
			
		i++;
		j--;
		i_glob++;
		j_glob--;
		if (i >= strlen(str[i_str]))
		{
			i = 0;
			i_str++;
		}
		if (j < 0)
		{
			j_str--;
			j = strlen(str[j_str]) - 1;
		}
	}
	return 1;
}

int char_is_in_str(char c, char *str)
{
	int i = 0;
	while (i < strlen(str))
	{
		if (c == str[i])
			return 1;
		i++;
	}
	return 0;
}

int del_str_from_str(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int i_new = 0;
	while (i < strlen(str2))
	{
		if (!char_is_in_str(str2[i], str1))
		{
			str2[i_new] = str2[i];
			i_new ++;
		}
		i++;
	}
	str2[i_new] = 0;
	return 0;
}

int transform(char*** A, int M, int N)
{
	int k = 0;
	int i, j;
	while ((k < M) && !is_pal(A[k], N))
		k++;
	if (k >= M)
		return -1;
	
	i = 0;
	j = 0;
	while (i < M)
	{
		if (i == k)
		{
			i++;
			continue;
		}
		j = 0;
		while (j < N)
		{
			del_str_from_str(A[k][j], A[i][j]);
			j++;
		}
		i++;
	}
}

int main(void)
{
	char ***A;
	int M, N;
	int i, j;
	FILE *input;
	input = fopen("input.txt", "r");
	A = read_matr(input, &M, &N);
	fclose(input);
	
	printf("%s %s\n%s %s\n", A[0][0], A[0][1], A[1][0], A[1][1]);
	printf("%d %d\n", is_pal(A[0], N), is_pal(A[1], N));
	transform(A, M, N);
	printf("%s %s\n%s %s\n", A[0][0], A[0][1], A[1][0], A[1][1]);
	i = 0;
	while (i < M)
	{
		j = 0;
		while (j < N)
		{
			free(A[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < M)
	{
		free(A[i]);
		i++;
	}
	free(A);
	
	return 0;
}
