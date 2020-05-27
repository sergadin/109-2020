#include <stdio.h>
#include <stdlib.h>
#include "f.h"

void a_read(FILE *inp, char ***a)
{
  int n, m;
  if (a_look(inp, a, n, m) != 0)
  {
	printf("no date");
	/*for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
		  printf ("%s " a[i][j]);
		}
		printf("\n");
	}*/
}
}

int a_look(FILE *inp, char ***a, int n, int m)
{
  char *str; 
  if ((a = (char***) malloc(n * sizeof(char**))) == NULL)
  {
    return -1;
  }
  for (int i = 0; i < n; i++)
  {
    if ((a[i] = (char**) malloc(m * sizeof(char**))) == NULL)
    {
      for (int j = 0; j < i; j++)
      {
        free(a[j]);
      }
      free(a);
      return -1;
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if ((str = str_r(inp)) == NULL || (a[i][j] = (char*)malloc((slen(str) + 1) * sizeof(char*))) == NULL)
      {
        for (int k = 0; k < j; k++)
        {
          free(a[i][k]);
        }
        free(a[i]);
        for (int k = 0; k < i; k++)
        {
          for (int l = 0; l < m; l++)
          {
            free(a[i][l]);
          }
          free(a[k]);
        }
        free (a);
        return -1;
      }
      a[i][j] = cop(str, a[i][j]);
      free(str);
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
	if(w = (char *)malloc(len + 1)) == NULL || len == 0)
		return str;
	for(int i = 0; i < len; i++)
	{
		w = str[len - 1 - i];
	}
	w[len] = 0
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
}