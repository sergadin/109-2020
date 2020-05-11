#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

char *read_long_string(FILE *f)
{
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s)
	{
		int len = strlen(s);
		char *result = malloc(len + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}
