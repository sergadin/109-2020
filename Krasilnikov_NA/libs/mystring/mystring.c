//All functions in library have prefix s- suggesting string"
#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

int slength(const char *string)
{
	int length = 0;
	while (string[length] != '\0')
	{
		length ++;
	}
	return length;
}

char *scopy(const char *from, char *to)
{
	int length;
	length = slength(from);
	for (int i = 0; i <= length; i++)
	{
		to[i] = from[i];
	}
	return to;
}

char *sread(FILE *fin)
{
	int N = 1024, cl = 1, bl; //cl = current_length, bl = buf_length 
	char *string, *buf;
	if ((buf = (char*)malloc(N)) == NULL)
	{
		return NULL;
	}
	if ((string = (char*)malloc(1)) == NULL)
	{
		free(buf);
		return NULL;
	}
	do
	{
		if (fgets(buf, N, fin) == NULL)
		{
			free(buf);
			free(string);
			return NULL;
		}
		bl = slength(buf);
		if ((string = (char*)realloc(string, cl + bl)) == NULL)
		{
			free(buf);
			free(string);
			return NULL;
		}
		scopy(buf, &string[cl - 1]);			
		cl += bl;
		if ((cl > 1) && (string[cl - 2] == '\n'))
		{
			string[cl - 2] = '\0';
			if ((string = (char*)realloc(string, cl - 1)) == NULL)
			{
				free(buf);
				free(string);
				return NULL;
			}
			break;
		}	
	}
	while (slength(buf) > 0);
	free(buf);
	return string;
}

