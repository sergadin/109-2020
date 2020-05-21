#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_SIZE 1024

int main() 
{
	FILE *original_file; //это наш главный файл
	FILE *include_file; //это наш файл, который мы инклюдим
	char **output_strings; //это массив строк, которые мы будем выводить
	int i = 0, j;
	const char *shablon = "#include ";
	char *include_file_name; //это строчка, куда будет записываться имя файла, который нужно заинклюдить
	int include_found;
	char *s;
	printf("length of shablon = %ld\n",strlen(shablon));

	output_strings = malloc(MAX_SIZE * sizeof(char *));

	original_file  = fopen("input.txt","r"); //открываем главный файл
	
	while((s = read_long_string(original_file)) != NULL) //пока читаются строки из файла
	{
		include_found = !strncmp(s,shablon,strlen(shablon)); //эта переменная показывает, нашли ли мы строку, начинающуюся с #include
		if(include_found) //если нашли, то...
		{
			printf("include found\n");
			include_file_name = malloc((strlen(s) - strlen(shablon)) * sizeof(char)); //выделяем память под имя инклюдируемого файла
			for(j = 0; j < strlen(s) - strlen(shablon) - 1; j++)
			{
				include_file_name[j] = s[j + strlen(shablon)]; //записываем в специальную строку имя файла, который нужно заинклюдить
			}
			include_file_name[strlen(s) - strlen(shablon) - 1] = 0;
			printf("include file name = %s\n",include_file_name);
			include_file = fopen(include_file_name,"r"); //открываем инклюдируемый файл
			free(s);
			free(include_file_name); //освобождаем место под имя файла
			while((s = read_long_string(include_file)) != NULL) //пока читаются строки из инклюдируемого файла
			{
				output_strings[i] = malloc((strlen(s)+1) * sizeof(char)); 
				output_strings[i] = strcpy(output_strings[i], s); //записываем их в массив
				printf("String %d\n",i+1);
				printf("%s",output_strings[i]);
				free(s);
				i++; //увеличиваем счётчик строк
			}
			fclose(include_file); //закрываем инклюдируемый файл
		}
		else
		{
			output_strings[i] = malloc((strlen(s)+1) * sizeof(char));
			output_strings[i] = strcpy(output_strings[i], s); //строку из массива строк главного файла записываем в массив выводимых строк
			free(s); //освобождаем строчку главного файла
			printf("String %d\n",i+1);
			printf("%s",output_strings[i]);
			i++; //увеличиваем счётчик строк
		}
	}
	fclose(original_file); //закрываем главный файл

	original_file = fopen("input.txt","w"); //снова открываем, теперь уже для записи в него
	for(j = 0; j < i; j++) //перезаписываем исходный файл
	{
		fprintf(original_file,"%s",output_strings[j]);
	}
	fclose(original_file);

	for(j = 0; j < i; j++)
	{
		free(output_strings[j]);
	}
	free(output_strings); //всех освобождаем
	return 0;
}
