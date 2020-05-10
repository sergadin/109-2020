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
	while((s = read_long_string(input)) != NULL) //считываем строчки из файла, пока тот не кончится
	{
		fprintf(stdout,"%s",s); //выводим строчку
		len = strlen(s); //считаем её длину

		for(i = 0; i < len - 1; i++) //проходим строку посимвольно
		{
			symbol = s[i];
			if(symbol != 32) //Если символ не пробел, то...
			{
				(*symbols)++; //Увеличиваем счётчик символов
				symbolstable[symbol]++; //Каждый символ кроме пробела заносим в табличку
				if(spaceind)
					(*words)++; //Если предыдущий символ был пробелом, то засчитываем новое слово
			}
			if(i == len - 2 && symbol != 32) //Если строка кончилась не пробелом, то...
				curr_word++; //увеличиваем длину текущего слова
			if(symbol == 32 || i == len - 2) //Если попался пробел или последний символ в строке
			{
				if(curr_word > *maxword)
					*maxword = curr_word; //при надобности обновляем рекорд максимальной длины слова
				if((*minword == 0) || (curr_word < *minword && curr_word > 0))
					*minword = curr_word; //и минимальной длины слова
				spaceind = 1; //включаем индикатор пробела
				curr_word = 0; //ставим длину текущего слова на 0
			}
			else //если же попался непоследний символ и не пробел, то...
			{
				spaceind = 0; //выключаем индикатор пробела
				curr_word++; //увеличиваем длину текущего слова
			}
		}
		free(s); //освобождаем строчку s
	}	
}

