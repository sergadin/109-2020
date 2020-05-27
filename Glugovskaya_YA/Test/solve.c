#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "solve.h"
#include "print.h"

void solve(char **a, int n, int m)
{
	int MinI = choose_string(a, n, m);
	if (print_res_file(a, n, m, MinI) == Open_Err)
		printf("Ошибка открытия\n"); 
}
	
int choose_string(char **a, int n, int m)
{
	char *buf1 = (char *) malloc(strlen(a[0])*sizeof(char));
	char *buf2 = (char *) malloc(strlen(a[m])*sizeof(char));
	int len1 = 0, len2 = 0, MinI = 0, Res = 0;
	
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			len1 += strlen(a[(i-1)*m+j]);
			buf1 = (char*)realloc(buf1, len1);
			strcat(buf1, a[(i-1)*m+j]);			
		}
		
		for (int j = 0; j < m; j++)
		{
			len2 += strlen(a[i*m+j]);
			buf2 = (char*)realloc(buf2, len2);
			strcat(buf2, a[i*m+j]);			
		}
		
		Res = strcmp(buf1, buf2);
		if (Res > 0) MinI = i;
		free(buf1);
		free(buf2);
	}
	return MinI;
}

