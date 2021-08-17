#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prog3-9.h"

const char* templ = "#include ";

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
	char *nextfilename;
	FILE *file;
	char *s;
	
	int i;
	int repeat = 0;

	for(i = 0; i < *listlength; i++)
	{
		if(!strcmp(filename,filelist[i]))
			repeat = 1;
	}
	if(repeat)
	{
		return filelist;
	}
	if((file = fopen(filename, "r")) == NULL)
	{
		return filelist;
	}

	filelist = realloc(filelist, *listlength + 1);

	filelist[*listlength] = malloc((strlen(filename)+1) * sizeof(char));

	strncpy(filelist[*listlength], filename, strlen(filename));

	filelist[*listlength][strlen(filename)] = 0;
	
	*listlength += 1;

	while((s = readstring(file)) != NULL)
	{
		if(strncmp(s, templ, 9) == 0)
		{
			nextfilename = malloc((strlen(s) - 8) * sizeof(char));
			strncpy(nextfilename, s + 9, strlen(s) - 8);
			nextfilename[strlen(s) - 9] = 0;
			filelist = include(output, nextfilename, filelist, listlength);
			printf("%ld \n", strlen(s));
			printf("%s \n", nextfilename);
			free(nextfilename);
		}
		else
		{
			fprintf(output, "%s", s);
		}
		printf("%s \n", s);
		free(s);
	}

	fclose(file);

	free(filelist[*listlength - 1]);
	filelist = realloc(filelist, *listlength);
	*listlength += -1;

	return filelist;
}