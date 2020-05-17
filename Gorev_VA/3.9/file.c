#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

int INCLUDE(char *progname);
int INCLUDE(char *progname)
{
	FILE *prog;
	char c = 0;
	char *A;
	char buf[N];
	int i, Ind, Eof = 0;
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("INCLUDE(%s): Can't open file \"%s\"\n", progname, progname);
		return -1;
	}
	
	i = 0;
	A = malloc(sizeof(char));
	A[0] = 0;
	while(!Eof)
	{
		if (fscanf(prog, "%c", &c) != 1)
			Eof = 1;
		else
		{
			if (c == '\r')
				continue;
			buf[i] = c;
			i++;
		}
		
		if ((i == N) || (c == '\n') || Eof)
		{
			int j = 0;
			A = (char*)realloc(A, (strlen(A) + 1 + N) * sizeof(char));
			while(j < i)
			{
				A[strlen(A) + 1] = 0;
				A[strlen(A)] = buf[j];
				j++;
			}
			i = 0;
		}
		if ((c == '\n') || Eof)
		{
			if (strstr(A, "#include ") == A)
			{
				if (A[strlen(A) - 1] == '\n')
				{
					A[strlen(A) - 1] = 0;
					Ind = 1;
				}
				else
					Ind = 0;
				if (strcmp(A + strlen("#include "), progname) == 0)
				{
					printf("INCLUDE(%s): Loop output: \"#include %s\" in the file \"%s\"\n", progname, progname, progname);
					fclose(prog);
					free(A);
					return -2;
				}
				else
				{
					if (INCLUDE(A + strlen("#include ")))
						return -3;
					if (Ind)
						printf("\n");
				}
			}
			else
				printf("%s", A);
			free(A);
			A = (char*)malloc(sizeof(char));
			A[0] = 0;
		}
	}
	
	free(A);
	fclose(prog);
	return 0;
}

int main(void)
{
	char *progname = "programm.txt";
	if (INCLUDE(progname))
		printf("ERROR\n");
	return 0;
}
