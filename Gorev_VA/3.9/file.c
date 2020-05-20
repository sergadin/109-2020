#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

struct chain
{
	char *filename;
	struct chain *prev;
};

char *read_str(FILE *prog, int *Eof);
char *read_str(FILE *prog, int *Eof)
{
	char *A;
	char c = 0;
	char buf[N];
	int i = 0;
	A = malloc(sizeof(char));
	A[0] = 0;
	while((c != '\n') && !(*Eof))
	{
		if (fscanf(prog, "%c", &c) != 1)
			*Eof = 1;
		else
		{
			if (c == '\r')
				continue;
			buf[i] = c;
			i++;
		}
		if ((i == N) || (c == '\n') || (*Eof))
		{
			int j = 0;
			A = (char*)realloc(A, (strlen(A) + 1 + i) * sizeof(char));
			while(j < i)
			{
				A[strlen(A) + 1] = 0;
				A[strlen(A)] = buf[j];
				j++;
			}
			i = 0;
		}
	}
	return A;
}

int check(char *filename, struct chain *Prev)
{
	struct chain *P = Prev;
	while(P != 0)
	{
		if (strcmp(filename, P->filename) == 0)
		{
			return -2;
		}
		P = P->prev;
	}
	return 0;
}

int INCLUDE(char *progname, struct chain *Prev);
int INCLUDE(char *progname, struct chain *Prev)
{
	FILE *prog;
	char *A;
	int Ind;
	int *Eof;
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("INCLUDE(%s): Can't open file \"%s\"\n", progname, progname);
		return -1;
	}
	
	A = (char*)malloc(2 * sizeof(char));
	A[0] = '\n';
	A[1] = 0;
	Eof = (int*)malloc(sizeof(int));
	*Eof = 0;
	while(!(*Eof))
	{
		free(A);
		A = read_str(prog, Eof);
		if (strstr(A, "#include ") == A)
		{
			if (A[strlen(A) - 1] == '\n')
			{
				A[strlen(A) - 1] = 0;
				Ind = 1;
			}
			else
				Ind = 0;
			//printf("~~%s", A);
			if (check(A + strlen("#include "), Prev))
			{
				printf("INCLUDE(%s): Loop output: \"#include %s\"\n", progname, A + strlen("#include "));
				fclose(prog);
				free(A);
				return -2;
			}
			else
			{
				struct chain *P;
				P = (struct chain*)malloc(sizeof(struct chain));
				P->filename = A + strlen("#include ");
				P->prev = Prev;
				if (INCLUDE(A + strlen("#include "), P))
				{
					free(P);
					return -3;
				}
				free(P);
				if (Ind)
				{
					A[strlen(A) + 1] = 0;
					A[strlen(A)] = '\n';
					printf("\n");
				}
			}
		}
		else
			printf("%s", A);
	}
	free(A);
	free(Eof);
	fclose(prog);
	return 0;
}

int main(void)
{
	char *progname = "programm.txt";
	struct chain *Prev;
	Prev = (struct chain*)malloc(sizeof(struct chain));
	Prev->filename = progname;
	Prev->prev = 0;
	if (INCLUDE(progname, Prev))
		printf("ERROR\n");
	free(Prev);
	return 0;
}
