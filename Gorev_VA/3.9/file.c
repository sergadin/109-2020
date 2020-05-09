#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM 1

int INCLUDE(char *progname, char *filename);
int INCLUDE(char *progname, char *filename)
{
	FILE *prog;
	FILE *file;
	char **A;
	char c;
	int N = 0, i = 0;
	char *incl = 0;
	int kNUM1, kNUM2;
	A = (char**)malloc(NUM * sizeof(char*));
	A[0] = (char*)malloc(NUM * sizeof(char));
	A[0][0] = 0;
	kNUM1 = kNUM2 = NUM;
	i = 0;
	while (i <= N)
	{
		printf("%s", A[i]);
		i++;
	}
	i = 0;
	while (i <= N)
	{
		free(A[i]);
		i++;
	}
	free(A);
	return 0;	
}

int main(void)
{
	char *filename = "input.txt";
	char *progname = "programm.txt";

	INCLUDE(progname, filename);

	return 0;
}
