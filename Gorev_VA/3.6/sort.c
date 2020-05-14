#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

char **ar_of_words(FILE* input)
{
	char **A;
	char c;
	char *str;
	int i = 0, j = 0, I, J;
	int kNUM1, kNUM2;
	kNUM1 = NUM;
	kNUM2 = NUM;
	A = (char**)malloc(kNUM1 * sizeof(char*));
	A[0] = (char*)malloc(kNUM2 * sizeof(char));
	A[0][0] = 0;
	//i - номер строчки, в которую мы будем записывать
	//j - номер буквы, которую мы будем записывать, в строчке

	while ((fscanf(input, "%c", &c) == 1)) // считываем символ
	{
		// если это нормальный символ, то его надо записать в слово
		if ((c != ' ') && (c != '\n') && (c != '	'))
		{
			if ((j + 2) > kNUM2)
			{
				kNUM2 += NUM;
				A[i] = (char*)realloc(A[i], kNUM2 * sizeof(char));
			}
			A[i][j] = c;
			j++;
			A[i][j] = 0;
		}
		else
			if (j > 0) // если символ ненормальный и мы еще не закончили старое слово, то его нужно закончить
			{
				if ((i + 2) > kNUM1)
				{
					kNUM1 += NUM;
					A = (char**)realloc(A, kNUM1 * sizeof(char*));
				}
				i++;
				kNUM2 = NUM;
				j = 0;
				A[i] = (char*)malloc(kNUM2 * sizeof(char));
				A[i][0] = 0;
			}
	}
	// на всякий случай в конец нужно добавить пустую строку
	if (j > 0)
	{
		A = (char**)realloc(A, (i + 2) * sizeof(char*));
		i++;
		j = 0;
		A[i] = (char*)malloc(1 * sizeof(char));
		A[i][0] = 0;
	}

	// сортировка
	I = i - 1;
	while (I > 0)
	{
		J = 0;
		while (J < I)
		{
			if (strcmp(A[J], A[J + 1]) > 0)
			{
				str = A[J];
				A[J] = A[J + 1];
				A[J + 1] = str;
			}
			J++;
		}
		I--;
	}

	return A;
}
