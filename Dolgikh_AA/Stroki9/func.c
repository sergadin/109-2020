#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

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

char *include(FILE *output, char *filename, char *filelist)
{
	char *nextfilename;
	FILE *file;
	char *s;
	const char* shablon = "#include ";
	
	int len = 0;
	int old_len = 0;
	char *check = strstr(filelist, filename);

	if(check != NULL)
	{
		printf("Змея укусила себя за хвост\n");
		return filelist;
	}

	if((file = fopen(filename, "r")) == NULL)
	{
		printf("Не удалось открыть файл\n");
		return filelist;
	}

	old_len = strlen(filelist);
	len = strlen(filelist) + strlen(filename);
	filelist = realloc(filelist, len+2);
	strncpy(filelist + old_len, filename, strlen(filename));
	filelist[len] = 32;
	filelist[len + 1] = 0;

	while((s = readstring(file)) != NULL)
	{
		if(strncmp(s, shablon, 9) == 0)
		{
			nextfilename = malloc((strlen(s) - 9) * sizeof(char));
			strncpy(nextfilename, s + 9, strlen(s) - 10);
			nextfilename[strlen(s) - 10] = 0;
			filelist = include(output, nextfilename, filelist);
			free(nextfilename);
		}
		else
		{
			fprintf(output, "%s", s);
		}
		free(s);
	}

	fclose(file);

	filelist = realloc(filelist, old_len);
	filelist[old_len - 1] = 0;

	return filelist;
}

