#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "solve.h"
#include "print.h"
#include <stdio.h>
#include <string.h>

int read(char **a, char *name)
{
	FILE*fp;
	int n, m;
	fp = fopen(name,"r");
	
	if (!fp) return Open_Err;
	fscanf(fp, "%d %d\n", &n, &m);
	//printf("%d %d\n", n, m);
	for (int i = 0; i < m*n; i++)
	{
		if ((a[i]=Read_Srt(fp)) == NULL)
		{
			fclose(fp);
			return Read_Err;
		}
		printf("a[%d] = %s\n", i, a[i]);
	}
	printf("Matrix A:\n");
	print(a, n, m);
	solve(a, n, m);
	
	fclose(fp);
	return All_Correct;
}

char *Read_Srt(FILE *FileIn)
{
	char buf[1024];
	char *result = (char*) malloc (1 * sizeof(char));
	char *s = (char*) malloc (1025 * sizeof(char));
	int len;
	buf[0] = 0;
	
	s = fgets(buf, 1024, FileIn);

	if(s)
	{
		len = strlen(s);
		result = (char *) malloc((len + 1)*sizeof(char));
		strcpy(result, s);
		
		if (len < 1023) return result;
		
		while((s) && (s[strlen(s) - 1] != '\n'))
		{
			s = fgets(buf, 1024, FileIn);
			len += strlen(s);
        	result = (char *) realloc(result, len);
			strcat(result, s);		
		}
		free(s);
		return result;
	}
	free(s);
	free(result);
	printf("%s\n", buf);
	return NULL;
}