#include"stdio.h"
#include"stdlib.h"
#include"findstr.h"
int len(char *s);
char *readstring(FILE *input);
char *strcpy(char *t, char *s);

void findstr(FILE *input, FILE *output, char *w) 
{
	int i, j;
        int k = -1;
	int p = 0, l = 0;
        int n1 = 0, n2 = 0;
	char *t;	
	while((t = readstring(input)) != NULL) 
	{	
		k = k + 1;
		l = len(t);
		n1 = len(w);
		for(i = 0; i < l; i++) 
		{
			if(t[i] == w[0])
			{
				for(j = 0; j < n1 + 1; j++)
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
			p = 0;
			
		}
		free(t);

	}	
	
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
	free(s);
	return NULL;
}

void ch_fl_wth_def(FILE * input, FILE * f_with_def)
{
	char * strnow;
	char * what;
	char * forwhat;
	const char * def;
	const char * undef;
	int l, lw, lf;

}


void str_of_def(char * allstr, char * what, char * forwhat, const char * def)
{
	int l = len(allstr);
	int i = 0;
	what = malloc(l + 1);
	forwhat = malloc(l + 1);
	while(allstr[i] == def[i])
		i++;
	i++;
	while(allstr[i] != ' ')
	{
		what[i] = allstr[i];
		i++;
	}
	what[i] = '\0'
	while(i <= l)
	{
		forwhat[i] = allstr[i];
		i++;
	}

}


