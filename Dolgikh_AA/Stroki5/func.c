#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

char *read_long_string(FILE *f)
{
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s)
	{
		int len = strlen(s);
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}

void FUNC(FILE *input, int *words, int *minword, int *maxword, int *symbols, int *symbolstable)
{
	char *s;
	int curr_word = 0; //это длина текущего слова
	long int i;
	int spaceind = 1; //это индикатор пробела в предыдущем символе
	int symbol; //это код считываемого символа
	*words = 0; //это счётчик слов
	*minword = 0; //это минимальная длина слова
	*maxword = 0; //это максимальная длина слова
	*symbols = 0; //это счётчик символов
	long int len;
	while((s = read_long_string(input)) != NULL)
	{
		fprintf(stdout,"%s",s);
		len = strlen(s);

		for(i = 0; i < len - 1; i++)
		{
			symbol = s[i];
			if(symbol != 32) //Каждый символ кроме пробела заносим в табличку
			{
				(*symbols)++;
				symbolstable[symbol]++;
				if(spaceind)
					(*words)++;
			}
			if(i == len - 2 && symbol != 32) //Если строка кончилась не пробелом
				curr_word++;
			if(symbol == 32 || i == len - 2) //Если попался пробел или кончилась строка
			{
				if(curr_word > *maxword)
					*maxword = curr_word;
				if((*minword == 0) || (curr_word < *minword && curr_word > 0))
					*minword = curr_word;
				spaceind = 1; 
				curr_word = 0; 
			}
			else
			{
				spaceind = 0; 
				curr_word++; 
			}
		}
		

	}	
	free(s);
}

