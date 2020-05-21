#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_SIZE 1024

int main() 
{
	FILE *original_file; //это наш главный файл
	FILE *include_file; //это наш файл, который мы инклюдим
	char **strings_of_original_file; //это массив строк главного файла
	char **output_strings; //это массив строк, которые мы будем выводить
	int i = 0, j;
	char shablon[8] = "#include"; 
	char *include_file_name; //это строчка, куда будет записываться имя файла, который нужно заинклюдить
	int include_not_found;
	char *s;

	strings_of_original_file = malloc(MAX_SIZE * sizeof(char *));
	output_strings = malloc(MAX_SIZE * sizeof(char *));

	original_file  = fopen("input.txt","r"); //открываем главный файл
	while((s = read_long_string(original_file)) != NULL) //пока читаются строки из файла
	{
		strings_of_original_file[i] = malloc((strlen(s)+1) * sizeof(char));
		strings_of_original_file[i] = strcpy(strings_of_original_file[i],s); //считавшуюся строку записываем в массив
		free(s);

		include_not_found = strncmp(strings_of_original_file[i],shablon,8); //эта переменная показывает, нашли ли мы строку, начинающуюся с #include
		if(!include_not_found) //если нашли, то...
		{
			include_file_name = malloc((strlen(strings_of_original_file[i]) - 9) * sizeof(char)); //выделяем память под имя инклюдируемого файла
			for(j = 0; j < strlen(strings_of_original_file[i]) - 10; j++)
			{
				include_file_name[j] = strings_of_original_file[i][j+9]; //записываем в специальную строку имя файла, который нужно заинклюдить
			}
			include_file_name[strlen(strings_of_original_file[i])-10] = 0;
			include_file = fopen(include_file_name,"r"); //открываем инклюдируемый файл
			free(strings_of_original_file[i]); //освобождаем строчку главного файла 
			free(include_file_name); //освобождаем место под имя файла
			while((s = read_long_string(include_file)) != NULL) //пока читаются строки из инклюдируемого файла
			{
				output_strings[i] = malloc((strlen(s)+1) * sizeof(char)); 
				output_strings[i] = strcpy(output_strings[i], s); //записываем их в массив
				free(s);
				i++; //увеличиваем счётчик строк
			}
			fclose(include_file); //закрываем инклюдируемый файл
		}
		else
		{
			output_strings[i] = malloc((strlen(strings_of_original_file[i])+1) * sizeof(char));
			output_strings[i] = strcpy(output_strings[i], strings_of_original_file[i]); //строку из массива строк главного файла записываем в массив выводимых строк
			free(strings_of_original_file[i]); //освобождаем строчку главного файла
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
	free(strings_of_original_file);
	free(output_strings); //всех освобождаем
	return 0;
}
