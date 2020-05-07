#include"stdio.h"
#include"stdlib.h"
#include"zamena.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);

void zamena(FILE *input1, FILE *output) 
{
	int i = 0, j, k = 1, len = 0, n = 0, num1, num2;
	char c;
	char *s;	
	while((s = read_string(input1)) != NULL)
	{
		len = length(s);
	        while(s[i] != '\0')
		{
		         fprintf(output, "%c", s[i]);
  			 while(s[i] == s[i+1])
			 {
				 i++;
   			 }
			 i++;
 		 }
		free(s);
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
	int n, i; 
	n = length(s);
	for (i = 0; i < n+1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

char *read_string(FILE *f) 
{
	int l = 0, l1 = 0;
	char *result;
	char buf[1024];
	buf[0] = 0;	
	char *s = fgets(buf, 1024, f);
	if(!s)
		return NULL;
	else
	{
		l = length(s);
		result = (char *) malloc((l + 1)*sizeof(char));
		strcpy(result, s);
		while((s) && (s[length(s)-1] != '\n'))
		{
			strcpy(result, s);
			l1 = length(s);
			l = l+l1;
			result = (char *) realloc(result, l);
			s = fgets(buf, 1024, f);
		}
		return result;
	}
}

