#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "change.h"

void change(const char *s, const char *old, const char *curr)
{
	char *result = NULL;
	int i, calc = 0, currlen = strlen(curr), oldlen = strlen(old);
	
		for (i = 0; s[i] != '\0'; i++)
		{
			if (strstr(&s[i], old) == &s[i])
			{
				i += oldlen - 1;
				calc++;
			}
		}
	
	result = (char*) malloc(i + 1 + calc*(currlen-oldlen));
	i = 0;

	while (*s)
	{
		if (strstr(s, old) == s)
		{
			strcpy(&result[i], curr);
			s+=oldlen;
			i+=currlen;
		}

		else
		{
			result[i++] = *s;
			s++;
		}
	}
	result[i] = '\0';
	printf("%s", result);
	free(result);
}


void read_file(FILE *file, char **data, int *size_array, size_t size_buffer)
{
	int i = 0;
	data[0] = NULL;
	while ((getline(&data[i], &size_buffer, file)) != -1)
	{
		data[i + 1] = NULL;
		i++;
	}
	*size_array = i;
}
