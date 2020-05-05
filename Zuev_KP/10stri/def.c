#include"stdio.h"
#include"stdlib.h"
#include"def.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);

void def(FILE *input1, FILE *output, const char *w1, const char *w2) 
{
	int i, j, k, p = 0, len = 0, n1 = 0, n2 = 0;
	char *t;	
	while ((t = read_string(input1)) != 0) 
	{
		len = length(t);
		n1 = length(w1);
		for (i = 0; i < len; i++) 
		{
			if (t[i] == w1[0])
			{
				for (j = 0; j < n1+1; j++)
				{
					if (t[i+j] == w1[j])
					{
						p = p+1;
					}
				}
			}
			if (p == n1)
			{
				for (j = 0; j < n1; j++)
				{
					t[i+j] = w2[j];
				}
			}
			p = 0;	
		}
		fprintf(output, "%s", t);	
		
	}	

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
		char *result = malloc(n + 1);
		strcpy(result, s);
		return result;
		free(result);
	}
	free(s);
	return 0;
}

