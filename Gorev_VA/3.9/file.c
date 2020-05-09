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

	//open file progname
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("Can't open file' %s\n", progname);
		return -1;
	}

	// create string "#include filename"
	incl = (char*)malloc((strlen("#include ") + strlen(filename) + 1) * sizeof(char));
	strcpy(incl, "#include ");
	strcpy(incl + strlen("#include "), filename);

	// create array of strings
	// A[i] - string in prog or contents of the file filename
	kNUM1 = kNUM2 = NUM;
	A = (char**)malloc(kNUM1 * sizeof(char*));
	A[0] = (char*)malloc(kNUM2 * sizeof(char));
	A[0][0] = 0;
	N = 0;
	while (fscanf(prog, "%c", &c) == 1)
	{
		// put char in string
		if ((strlen(A[N]) + 2) > kNUM2)
		{
			kNUM2 += NUM;
			A[N] = (char*)realloc(A[N], kNUM2 * sizeof(char));
		}
		A[N][strlen(A[N]) + 1] = 0;
		A[N][strlen(A[N])] = c;

		// if c == '\n' we must check equal to "#include filename" and create new string
		if (c == '\n')
		{
			//create new string
			if ((N + 2) > kNUM1)
			{
				kNUM1 += NUM;
				A = (char**)realloc(A, kNUM1 * sizeof(char*));
			}
			N++;
			kNUM2 = NUM;
			A[N] = (char*)malloc(kNUM2 * sizeof(char));
			A[N][0] = 0;
		}
	}






	//write all
	//prog = fopen(progname, "w");
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
	free(incl);
	fclose(prog);
	return 0;
}

int main(void)
{
	char *filename = "input.txt";
	char *progname = "programm.txt";

	INCLUDE(progname, filename);

	return 0;
}

