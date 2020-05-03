#include"stdio.h"
#include"stdlib.h"
#include"zamena.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);

void zamena(FILE *input1, FILE *output) 
{
	int len;
	char *t;	
	while (!((t = read_string(input1)) == NULL)) 
	{
		len = length(t);
		printf("%d\n", len);	
		fprintf(output, "The string is: '%s'\n", t);
	}
	free(t);
}

int length(const char *s) 
{
	int n = 0;
	while (s[n] != 0) 
	{
		n++;
	}	
	return n;
}

char *strcpy(char *t, const char *s) 
{
	int n; 
	n = length(s);
	for (int i = 0; i < n + 1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

char *read_string(FILE *f) 
{
	char buf[1024];
	buf[0] = 0;
	char *s = fgets(buf, 1024, f);
	if(s) 
	{
		int n = length(s);
		char *result = malloc(n + 1);
		strcpy(result, s);
		return result;
	}
	return NULL;
}








