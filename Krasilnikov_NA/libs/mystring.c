//All functions in library have prefix s- suggesting string"
#include <stdio.h>
#include <stdlib.h>

#include "mystring.h"

int slength(char *string)
{
	int length = 0;
	while (string[length] != '\0')
	{
		length ++;
	}
	return length;
}

char *scopy(char *from, char *to)
{
	int length = slength(from);
	if ((*to = (char*)realloc(to, length + 1) == NULL))
	{
		return NULL;
	}
	for (int i = 0; i < length; i++)
	{
		to[i] = from[i];
	}
	to[length] = '\0';
	return to;
}
