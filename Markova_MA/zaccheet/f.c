#include <stdio.h>
#include <stdlib.h>
#include "f.h"

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