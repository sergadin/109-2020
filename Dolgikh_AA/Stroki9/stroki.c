#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

#define MAX_SIZE 1024

int main() 
{
	FILE *original_file;
	FILE *include_file;
	char **strings_of_original_file;
	char **strings_of_include_file;
	int j, i = 0;
	char shablon[8] = "#include";
	char *include_file_name;
	int include_not_found;

	strings_of_original_file = malloc(MAX_SIZE * sizeof(char *));
	strings_of_include_file = malloc(MAX_SIZE * sizeof(char *));

	original_file  = fopen("input.txt","r");
	while((strings_of_original_file[i] = read_long_string(original_file)) != NULL)
	{
		include_not_found = strncmp(strings_of_original_file[i],shablon,8); //эта переменная показывает, нашли ли мы строку, начинающуюся с #include
		if(!include_not_found) //если нашли, то...
		{
			include_file_name = malloc(MAX_SIZE * sizeof(char));
			for(j = 0; j < strlen(strings_of_original_file[i]) - 10; j++)
			{
				include_file_name[j] = strings_of_original_file[i][j+9]; //записываем в специальную строку имя файла, которую нужно заинклюдить
			}
			include_file = fopen(include_file_name,"r");
			j = 0;
			while((strings_of_include_file[j] = read_long_string(include_file)) != NULL)
			{
				strings_of_original_file[i] = strings_of_include_file[j]; //записываем строки включаемого файла в исходный файл
				i++;
				j++;
			}
			fclose(include_file);
			free(include_file_name);
		}
		else
		{
			i++;
		}
	}
	fclose(original_file);

	original_file = fopen("input.txt","w");
	for(j = 0; j < i; j++) //перезаписываем исходный файл
	{
		fprintf(original_file,"%s",strings_of_original_file[j]);
	}
	fclose(original_file);

	for(i = 0; i < MAX_SIZE; i++)
	{
		free(strings_of_original_file[i]);
		free(strings_of_include_file[i]);
	}
	free(strings_of_original_file);
	free(strings_of_include_file);
	return 0;
}
