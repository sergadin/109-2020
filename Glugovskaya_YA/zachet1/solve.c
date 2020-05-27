#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "solve.h"
#include "print.h"

void solve(char **a, int n, int m)
{
	int MinI = choose_string(a, n, m);
	printf("Egc2\n");
	if (print_res_file(a, n, m, MinI) == Open_Err)
		printf("Ошибка открытия\n"); 
}
	
	
int choose_string(char **a, int n, int m)
{
	int MinI = 0, St1, St2, El1, El2, len, len1 = 0, len2 = 0;
	for (int i = 1; i < n; i++)
	{
		len1 = len2 = 0;
		for (int j = 0; j < m; j++)
		{
			len1 += strlen(a[i*m+j]) - 1;
			len2 += strlen(a[(i-1)*m+j]) - 1;
		}
		if (len1 < len2) len = len1;
		else len = len2;
		St1 = St2 = 0;
		for (int k = 0; k < len; k++)
		{
			if (El1 >= strlen(a[(i-1)*m+St1]) - 2){
				St1++;
				El1 = 0;
			}
			if (El2 >= strlen(a[i*m+St2]) - 2){
				St2++;
				El2 = 0;
			}

			if ((int)(a[(i-1)*m+St1][El1]) > (int)(a[i*m+St2][El2]))
			{
				printf("%s и %s\n", a[(i-1)*m+St1], a[i*m+St2]);
				MinI=i;
				break;
			}
			El1++;
			El2++;
		}
	
	}
	printf("MinI %d\n", MinI);
	return MinI;		
}
	

/*int choose_string(char **a, int n, int m)
{
	char *buf1 = (char *) malloc(1*sizeof(char));
	char *buf2 = (char *) malloc(1*sizeof(char));
	int len1 = 0, len2 = 0, MinI = 0, Res = 0;
	
	for (int i = 1; i < n; i++)
	{
		len1 = 0;
		len2 = 0;
		for (int j = 0; j < m; j++)
		{
			printf("i %d j %d\n", i, j);
			len1 += strlen(a[(i-1)*m+j]);
			printf("len %s = %d\n",a[(i-1) * m + j], len1);
			buf1 = (char*) realloc (buf1, len1);
			strcat(buf1, a[(i-1)*m+j]);	
			len2 += strlen(a[i*m+j]);
			buf2 = (char*)realloc(buf2, len2);
			strcat(buf2, a[i*m+j]);	
		}
		Res = strcmp(buf1, buf2);
		if (Res > 0) MinI = i;
		free(buf1);
		free(buf2);
	}
	printf("Eg4\n");
	return MinI;
}
*/
