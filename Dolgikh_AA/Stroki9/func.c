#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

const char* shablon = "#include ";

char *readstring(FILE *input)
{
	int l, p = 0;
	char *res;
	char buf[1024];
	char *s;
	s = fgets(buf, 1024, input);
	if(s)
	{
		l = strlen(s);
		res = (char *)malloc((l + 1) * sizeof(char));
		strcpy(res, s);
		while((s) && (s[strlen(s) - 1] != '\n'))
		{
			strcpy(res, s);
			s = fgets(buf, 1024, input);
			if(s)
			{
				p = strlen(s);
				l += p;
				res = (char *)realloc(res, 1);
			}
		}
		return res;
	}
	return NULL;
}

char **include(FILE *output, char *filename, char **filelist, int *listlength)
{
	printf("Начинаем работу с файлом %s\n",filename);
	char *nextfilename;
	FILE *file;
	char *s;
	
	int i;
	int repeat = 0;

	printf("Ищем файл в списке\n");
	//Ищем наш файл в списке
	for(i = 0; i < *listlength; i++)
	{
		if(!strcmp(filename,filelist[i]))
			repeat = 1;
	}
	//Если нашли, то случился повтор, и всё плохо
	if(repeat)
	{
		printf("Змея укусила себя за хвост\n");
		return filelist;
	}
	printf("Не нашли\n");
	//Открываем наш файл
	if((file = fopen(filename, "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return filelist;
	}
	printf("Открыли файл %s\n", filename);
	//Добавляем наш файл в список
	printf("Реаллочим наш список на размер %d\n",*listlength+1);
	filelist = realloc(filelist, *listlength + 1);
	printf("Выделяем память под имя нашего файла в списке\n");
	filelist[*listlength] = malloc((strlen(filename)+1) * sizeof(char));
	printf("Записываем наш файл в список\n");
	strncpy(filelist[*listlength], filename, strlen(filename));
	filelist[*listlength][strlen(filename)] = 0;
	*listlength += 1;

	//Читаем строчки из нашего файла
	while((s = readstring(file)) != NULL)
	{
		if(strncmp(s, shablon, 9) == 0)
		{
			nextfilename = malloc((strlen(s) - 9) * sizeof(char));
			strncpy(nextfilename, s + 9, strlen(s) - 10);
			nextfilename[strlen(s) - 10] = 0;
			filelist = include(output, nextfilename, filelist, listlength);
			free(nextfilename);
		}
		else
		{
			fprintf(output, "%s", s);
		}
		free(s);
	}

	fclose(file);

	free(filelist[*listlength - 1]);
	filelist = realloc(filelist, *listlength);
	*listlength += -1;

	return filelist;
}

