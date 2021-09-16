  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog3-6.h"

void PRINT(char **arr_of_words);

void PRINT(char **arr_of_words)
{
	int i = 0;
	while(strlen(arr_of_words[i]) > 0)
	{
		printf("%s\n", arr_of_words[i]);
		i++;
	}
}

int main()
{
	char **array;
	FILE* input;
	if((input = fopen("input.txt","r")) == NULL)
	{
		printf("A problem has occured with opening the input file\n");
		return -1;
	}
	array = sort_file(input);
	PRINT(array);
	return 0;
}
