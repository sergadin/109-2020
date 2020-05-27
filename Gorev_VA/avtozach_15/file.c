#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ***read_matr(FILE *input)
{
	int M, N;
	int i = 0, j = 0;
	char ***A;
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
	char *Q;
	Q = (char*)malloc(100 * sizeof(char));
	fgets(Q, 100, input);
	while (i < M)
	{
		j = 0;
		while (j < N)
		{
			A[i][j] = (char*)malloc(100 * sizeof(char));
			fgets(A[i][j], 100, input);
			printf("%s", A[i][j]);
			j++;
		}
		i++;
	}
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
	
	i = 0;
	j = strlen(str[size_of_str - 1]) - 1;
	i_glob = 0;
	j_glob--;
	i_str = 0;
	j_str = size_of_str - 1;
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
			return 0;
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
		
		i++;
	}
}

int main(void)
{
	char ***A;
	int M, N;
	FILE *input;
	input = fopen("input.txt", "r");
	A = read_matr(input);
	/*A = (char***)malloc(M * sizeof(char**));
	A[0] = (char**)malloc(N * sizeof(char*));
	A[1] = (char**)malloc(N * sizeof(char*));	
	
	A[0][0] = "kjk";
	A[0][1] = "ababba";
	A[1][0] = "1234";
	A[1][1] = "321";
	
	printf("%s %s\n%s %s\n", A[0][0], A[0][1], A[1][0], A[1][1]);
	printf("%d %d\n", is_pal(A[0], N), is_pal(A[1], N));
	//del_str_from_str(A[1][1], A[1][0]);
	//A[0][0][0] = 'a';
	//printf("%s", A[0][0]);*/

	return 0;
}
