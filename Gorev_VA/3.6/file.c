#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

void Print(char **A);
void Print(char **A)
{
	int i = 0;
	while(strlen(A[i]) > 0)
	{
		printf("%s\n", A[i]);
		i++;
	}
}

int main(void)
{
	char **s;
	int i = 0;
	FILE *input;
	if ((input = fopen("input.txt", "r")) == NULL)
	{
		printf("Не удалось открыть файл input.txt\n");
		return -1;
	}
	
	s = ar_of_words(input);
	Print(s);

	while (strlen(s[i]) > 0)
	{
		free(s[i]);
		i++;
	}
	free(s[i]);
	free(s);
	fclose(input);
	return 0;
}
