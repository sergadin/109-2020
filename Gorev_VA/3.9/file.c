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
	int N, i;
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
	// A[i] - string in prog or contents of the file
	A = (char**)malloc(NUM * sizeof(char*));
	A[0] = (char*)malloc(NUM * sizeof(char));
	A[0][0] = 0;
	kNUM1 = kNUM2 = NUM;

	//write all
	//prog = fopen(progname, "w");
	i = 0;
	while (i <= N)
	{
		printf("%s", A[i]);
		i++;
	}

	//fclose(prog);
	i = 0;
	while (i <= N)
	{
		free(A[i]);
		i++;
	}
	free(A);
	free(incl);
	return 0;
}

int main(void)
{
	char *filename = "input.txt";
	char *progname = "programm.txt";

	INCLUDE(progname, filename);

	return 0;
}
