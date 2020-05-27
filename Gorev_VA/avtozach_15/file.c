#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _N 2

/*
** Считывание строки из файла input
** считывание проходит до конца файла, либо до символа '\n'
** создает и возвращает считанную строку
*/
char *read_str(FILE *input);
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

/*
** Считывает и создает матрицу строк char ***A из файла input размера M строк на N столбцов
** В первой строке должны быть записаны число строк M и число столбцов N
** Далее должны быть записаны элементы матрицы в порядке (номер строки) * N + (номер столбца)
** Они записываются по входящим адресам *m и *n соответственно
** Входные данные должны иметь следующий вид:
** M N
** A[0][0]
** A[0][1]
** A[0][2]
** ...
** A[M - 1][N - 1]
** Возвращает считанную матрицу А
*/
char ***read_matr(FILE *input, int *m, int *n);
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

/*
** Записывает матрицу строк char ***matr из файла input размера M строк на N столбцов
** В первой строке записываются число строк M и число столбцов N
** Далее записываются элементы матрицы в порядке (номер строки) * N + (номер столбца)
** Выходные данные имеют следующий вид:
** M N
** matr[0][0]
** matr[0][1]
** matr[0][2]
** ...
** matr[M - 1][N - 1]
*/
int write(FILE *output, char ***matr, int M, int N);
int write(FILE *output, char ***matr, int M, int N)
{
	int i, j;
	fprintf(output, "%d %d\n", M, N);
	i = 0;
	while (i < M)
	{
		j = 0;
		while (j < N)
		{
			fprintf(output, "%s\n", matr[i][j]);
			j++;
		}
		i++;
	}
	return 0;
}

/*
** Вычисляет, является ли строка char **str, состоящая из size_of_str подстрок палиндромом
** Возвращает 1, если str - палиндром и 0 иначе
*/
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

/*
** Вычисляет, содержится ли символ char c в строке char *str
** Возвращает 1, если символ char с содержится в строке char *str и 0 иначе
*/
int char_is_in_str(char c, char *str);
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

/*
** Удаляет символы, встречающиеся в строке char *str1 из строки char *str2
** Записывает полученную строку по адресу str2
** Выделенная на str2 память не меняется
*/
int del_str_from_str(char *str1, char *str2);
int del_str_from_str(char *str1, char *str2)
{
	int i = 0;
	int j = 0;
	int i_new = 0;
	while (i < strlen(str2))
	{
		if (char_is_in_str(str2[i], str1))
		{
			str2[i_new] = str2[i];
			i_new ++;
		}
		i++;
	}
	str2[i_new] = 0;
	return 0;
}

/*
** Находит в матрице char ***A строку с наименьшим номером A[k], являющуюся палиндромом
** Если таких строк нет, возвращает -1
** Если такая строка нашлась, удаляет из всех строк A[i][j], где i != k, символы, встречающиеся в строке A[k][j] и возвращает 0
** Например: такая матрица
** abc4 def4
** 1234 321
** преобразуется следующим образом:
** abc def4
** 1234 321
*/
int transform(char*** A, int M, int N);
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
	return 0;
}

int main(int argc, char **argv)
{
	char ***A;
	int M, N;
	int i, j;
	char *fileinput = argv[1];
	FILE *input;
	FILE *output;
	if ((input = fopen(fileinput, "r")) == 0)
	{
		return -1;
	}
	if ((output = fopen("output.txt", "w")) == 0)
	{
		fclose(input);
		return -1;
	}
	
	A = read_matr(input, &M, &N);
	transform(A, M, N);
	write(output, A, M, N);
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
	fclose(input);
	fclose(output);
	return 0;
}
