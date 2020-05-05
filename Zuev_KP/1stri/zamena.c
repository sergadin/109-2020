#include"stdio.h"
#include"stdlib.h"
#include"zamena.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);

void zamena(FILE *input1, FILE *output) 
{
	int i, j, k, len = 0, n = 0;
	char *t;	
	while ((t = read_string(input1)) != NULL) 
	{
		k = 1;
		len = length(t);
		n = len;
		for (i = 0; i < len; i++) 
		{
			if (t[i] == t[i+1])
			{
				n = n-1; 
			}
		}
		char *f = malloc(n+1* sizeof(char));
		for (i = 0; i < len; i++) 
		{		
			f[0] = t[0];
			if (t[i] != t[i+1])
			{
				for (j = k; j < n+1; j++) 
				{
					f[j] = t[i+1];							
				}
				k = k+1;
			}
		}
		fprintf(output, "%s\n", f);
		free(f);
	}	
	free(t);
}

int length(const char *s) 
{
	int n = 0;
	while (*s++) 
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
		char *result = malloc(n+1* sizeof(char));
		strcpy(result, s);
		return result;
		free(result);
	}
	free(s);
	return 0;
}

