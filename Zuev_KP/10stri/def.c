#include"stdio.h"
#include"stdlib.h"
#include"def.h"
int length(const char *s);
char *read_string(FILE *f);
char *strcpy(char *t, const char *s);

void def(FILE *input1, FILE *output, const char *w1, const char *w2, const char *define, const char *undef) 
{
	int i, j, k = -1, p = 0, len = 0, n1 = 0, n2 = 0;
	char *t;
	char *s;	
	while ((t = read_string(input1)) != 0) 
	{
		len = length(t);
		n1 = length(w1);
		n2 = length(w2);
		for (i = 0; i < len; i++) //замена privet на hello 
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
				if (n1>=n2)
				{
					for (j = 0; j < n2; j++)
					{
						t[i+j] = w2[j];
					}
					for (j = n2; j < n1; j++)
					{
						t[i+j] = 32;
					}
				}
			}
			p = 0;	
		}
		len = length(t);
		n1 = length(define);
		for (i = 0; i < len; i++) //удаление define
		{
			p = 0;
			if (t[i] == define[0])
			{
				for (j = 0; j < n1+1; j++)
				{
					if (t[i+j] == define[j])
					{
						p = p+1;
					}
				}
			}
			if (p == n1)
			{
					for (j = 0; j < n1; j++)
					{
						t[i+j] = 32;
					}	
			}
				
		}
		len = length(t);
		n2 = length(undef);
		for (i = 0; i < len; i++) //удаление undef
		{
			p = 0;
			if (t[i] == undef[0])
			{
				for (j = 0; j < n2+1; j++)
				{
					if (t[i+j] == undef[j])
					{
						p = p+1;
					}
				}
			}
			if (p == n2)
			{
					for (j = 0; j < n2; j++)
					{
						t[i+j] = 32;
					}	
			}
				
		}
		fprintf(output, "%s", t);
		free(t);					
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
	int l, l1;
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
		while((s) && (s[length(s) - 1] != '\n'))
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




/*
while ((s = read_string(input2)) != 0) 	
	{
		len = length(s);
		n1 = length(define);
		for (i = 0; i < len; i++) //удаление define
		{
			p = 0;
			if (s[i] == define[0])
			{
				for (j = 0; j < n1+1; j++)
				{
					if (s[i+j] == define[j])
					{
						p = p+1;
					}
				}
			}
			if (p == n1)
			{
					for (j = 0; j < n1; j++)
					{
						s[i+j] = 32;
					}	
			}
				
		}
		len = length(t);
		n2 = length(undef);
		for (i = 0; i < len; i++) //удаление undef
		{
			p = 0;
			if (s[i] == undef[0])
			{
				for (j = 0; j < n2+1; j++)
				{
					if (s[i+j] == undef[j])
					{
						p = p+1;
					}
				}
			}
			if (p == n2)
			{
					for (j = 0; j < n2; j++)
					{
						s[i+j] = 32;
					}	
			}
				
		}
		fprintf(output, "%s", s);
		free(s);					
	}
*/

























