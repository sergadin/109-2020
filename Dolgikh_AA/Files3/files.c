#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>

char **file_names_array;
int array_size = 0;

static int names_finder(const char *path, const struct stat *stat, int ind)
{
	if(ind == FTW_F)
	{
		char *name = strrchr(path, '/');

		if(name != NULL)
		{
			file_names_array = realloc(file_names_array, (array_size + 1) * sizeof(char*));
			file_names_array[array_size] = malloc((strlen(name) + 1) * sizeof(char));
			strcpy(file_names_array[array_size], name);
			array_size += 1;
		}
	}
	return 0;
}

static int names_comparator(const char *path, const struct stat *stat, int ind)
{
	int coinc;
	if(ind == FTW_F)
	{
		coinc = 0;
		char *name = strrchr(path, '/');
		if(name != NULL)
		{
			for(int i = 0; i < array_size; i++)
			{
				if(!strcmp(file_names_array[i], name))
				{
					coinc = 1;
					break;
				}
			}
		}
		if(coinc)
			printf("%s\n", name);
	}
}

int main(int argc, char **argv)
{
	if(argc == 3)
	{
		ftw(argv[1], names_finder, 10);
		ftw(argv[2], names_comparator, 10);
	}
	else
	{
		printf("Wrong arguments\n");
		return -1;
	}

	for(int i = 0; i < array_size; i++)
		free(file_names_array[i]);

	free(file_names_array);
}
