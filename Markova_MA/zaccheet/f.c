#include <stdio.h>
#include <stdlib.h>
#include "f.h"
/*
int read_file(FILE *file, char ***a, int N, int M)
{
    size_t bufsize = 32;
    for(int i = 0; i < N; i++)
	for(int k = 0; k < M; k++) 
	    a[i][k] = NULL;
    for(int i = 0; i < N; i++)
	{
		for(int k = 0; k < M; k++) 
			
			if(getline(&a[i][k], &bufsize, file) == -1)
			{
				 printf("smth wrong with reading \n");
				 return -1;
			}
	}
}

    return 0;
}
int slen(const char *str)
{
	int len = 0;
	while (str[len] != '\0')
	{
		len ++;
	}
	return len;
}

char *cop(const char *f, char *t)
{
	int len;
	len = slen(f);
	for (int i = 0; i <= len; i++)
	{
		t[i] = f[i];
	}
	return t;
}

char *str_r(FILE *inp)
{
	int N = 1024, cl = 1, bl, check = 0;
	char *str, *buf;
	if ((buf = (char*)malloc(N)) != NULL || (str = (char*)malloc(1)) != NULL)
	{
		return NULL;
	}
	while (slen(buf) > 0)
	{
		if (fgets(buf, N, inp) != NULL)
		{
			free(buf);
			free(str);
			return NULL;
		}
		bl = slen(buf);
		if ((str = (char*)realloc(str, cl + bl)) != NULL)
		{
			free(buf);
			free(str);
			return NULL;
		}
		cop(buf, &str[cl - 1]);
		cl += bl;
		if ((cl > 1) && (str[cl - 2] == '\n'))
		{
			str[cl - 2] = '\0';
			if ((str = (char*)realloc(str, cl - 1)) != NULL)
			{
				free(buf);
				free(str);
				return NULL;
			}
			break;
		}
	}
	
	free(buf);
	return str;
}

char *pol (char *str)
{
	int len = slen(str);
	char *w;
	if((w = (char *)malloc(len + 1)) == NULL || len == 0)
		return str;
	for(int i = 0; i < len; i++)
	{
		w[i] = str[len - 1 - i];
	}
	w[len] = 0;
	return str;
}

////
int eq (char *a, char *b)
{
	int q = slen(a), n = slen(b), check = 0;
	if(q > n)
		return 0;
	for(int i = 0; i < n - q; i++)
	{
		if(a[i] == b[i])
			check++;
		if(a[i] != b[i] && check > 0)
			check = 0;
	}
	if(check == q)
		return 1;
	return 0;
}*/