#include"stdio.h"
#include"stdlib.h"
#include"findstr.h"
int len(char *s);
char *readstring(FILE *input);
char *strcpy(char *t, char *s);

void findstr(FILE *input, FILE *output, char *w) 
{
	if(len(w) > 1)
	{
		int i, j;
        	int k = -1;
		int p = 0, le = 0;
       		int n1 = 0, n2 = 0;
		char *t;	
		while((t = readstring(input)) != NULL) 
		{
			k = k + 1;
			le = len(t);
			n1 = len(w);
			for(i = 0; i < le; i++) 
			{
				p = 0;
				if(t[i] == w[0])
				{
					for(j = 0; j < n1; j++)
					{	
						if(t[i + j] == w[j])
						{	
							p = p + 1;
						}
					}
				}
				if(p == n1)
				{
					fprintf(output, "%d:%d\n", k, i);
				}
				
				
			}
			free(t);
		}
	}
	else
		fprintf(output, "nenenenene");	
	
}

int len(char *s) 
{
	int n = 0;
	while (*s++) 
	{
		n++;
	}	
	return n;
}

char *strcpy(char *t, char *s) 
{
	int n; 
	n = len(s);
	for (int i = 0; i < n + 1; i++) 
	{
		t[i] = s[i];
	}
	return t;
}

char *readstring(FILE * input)
{
	int l, p = 0;
	char *res;
	char buf[1024];
	char *s;
	s = fgets(buf, 1024, input);
	if(s)
	{
		l = len(s);
		res = (char *) malloc((l + 1)*sizeof(char));
		strcpy(res, s);
		while((s) && (s[len(s) - 1] != '\n'))
		{
			strcpy(res, s);
			s = fgets(buf, 1024, input);
			if(s)
			{
				p = len(s);
				l += p;
		        	res = (char *) realloc(res, l);
			}
		
		}
		
		return res;
	}
	return NULL;
}



