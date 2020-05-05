#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void FUNC(FILE *input, char *s, int *words, int *minword, int *maxword, int *symbols, int *symbolstable)
{
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
			if(symbol == 32 || i == len - 2) //Если попался пробел или кончилась строка
			{
				if(curr_word > *maxword)
					*maxword = curr_word;
				if((*minword == 0) || (curr_word < *minword))
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

}

void func(char *s, long int len, int *words, int *minword, int *maxword, int *symbols, int *symbolstable)
{
	int curr_word = 0; //это длина текущего слова
	long int i;
	int spaceind = 1; //это индикатор пробела в предыдущем символе
	int symbol; //это код считываемого символа

	*words = 0; //это счётчик слов
	*minword = 0; //это минимальная длина слова
	*maxword = 0; //это максимальная длина слова
	*symbols = 0; //это счётчик символов

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
		if(symbol == 32 || i == len - 2) //Если попался пробел или кончилась строка
		{
			if(curr_word > *maxword)
				*maxword = curr_word;
			if((*minword == 0) || (curr_word < *minword))
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

int main(void)
{
	FILE *input;
	char *s;
	int i;
	long int len;
	int *symbolstable;
	int words, minword, maxword, symbols;
	
	symbolstable = (int *)malloc(256 * sizeof(int));
	for(i = 0; i < 256; i++)
		symbolstable[i] = 0;

	input = fopen("input.txt","r");
	
	while((s = read_long_string(input)) != NULL)
	{
		fprintf(stdout,"%s",s);
		len = strlen(s);
		func(s, len, &words, &minword, &maxword, &symbols, symbolstable);
		fprintf(stderr, "words: %d min: %d max: %d symbols: %d\n", words, minword, maxword, symbols);
		for(i = 0; i < 256; i++)
		{
			if(symbolstable[i] != 0)
				fprintf(stdout, "symbol %c: %d times\n", i, symbolstable[i]);
		}
	}

	/*FUNC(input, s, &words, &minword, &maxword, &symbols, symbolstable);
	fprintf(stderr, "words: %d min: %d max: %d symbols: %d\n", words, minword, maxword, symbols);
	for(i = 0; i < 256; i++)
	{
		if(symbolstable[i] != 0)
			fprintf(stdout, "symbol %c: %d times\n", i, symbolstable[i]);
	}*/
	fclose(input);
	free(s);
	free(symbolstable);
	return 0;
}
