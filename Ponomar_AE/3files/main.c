#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <sys/stat.h>

	
char **data;
int calc_names = 0;

static int get_names(const char *file, const struct stat *sb, int flag)
{
	if (flag == FTW_F)
        {	
		char *temp, *temp1;
		temp = strchr(file, '/');
		temp1 = strrchr(file, '/');
		if (temp != NULL && temp1 != NULL && temp == temp1)
		{
			data = realloc(data, (calc_names + 1)* sizeof(char*));
			data[calc_names] = malloc((strlen(temp) + 1) * sizeof(char));
			strcpy(data[calc_names], temp);
			calc_names++;
		}
	}

	return 0;
}


static int compare_names(const char *file, const struct stat *sb, int flag)
{
	int name = 0;

	if (flag == FTW_F)
        {	
		char *filename, *filename1;
		filename = strrchr(file, '/');
		filename1 = strchr(file, '/');
		if (filename != NULL && filename == filename1)
		{
			for (int i = 0; i < calc_names; i++)
			{
				if (strstr(data[i], filename))
				{
					name = 1;
					break;
				}
			}
		}

		if (name == 1)
		{
			printf("%s\n", filename);
		}
	}

	return 0;
}


int main(int argc, char **argv)
{
	int result;
	char *dir1 = argv[1], *dir2 = argv[2];

	if (argc == 3)
	{
		ftw(argv[1], get_names, 10);
		ftw(argv[2], compare_names, 10);
	}

	return 0;
}
