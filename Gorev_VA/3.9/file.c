#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 6

struct chain
{
	char *filename;
	struct chain *prev;
};

char *file_name(char *filename);
char *file_name(char *filename)
{
	char *new_name;
	if (strlen(filename) < strlen("#include "))
		return 0;
	if (strncmp(filename, "#include ", strlen("#include ")) != 0)
		return 0;
	
	if (filename[strlen(filename) - 1] == '\n')
	{
		new_name = (char*)malloc((strlen(filename) - strlen("#include ")) * sizeof(char));
		strncpy(new_name, filename + strlen("#include "), strlen(filename) - strlen("#include ") - 1);
		new_name[strlen(filename) - strlen("#include ") - 1] = 0;
	}
	else
	{
		new_name = (char*)malloc((strlen(filename) + 1 - strlen("#include ")) * sizeof(char));
		strcpy(new_name, filename + strlen("#include "));
	}
	return new_name;
}

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

int check(char *filename, struct chain *Prev);
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
	char *filename;
	int Ind;
	int Eof;
	if ((prog = fopen(progname, "r")) == NULL)
	{
		printf("INCLUDE(%s): Can't open file \"%s\"\n", progname, progname);
		return -1;
	}
	
	A = (char*)malloc(2 * sizeof(char));
	A[0] = '\n';
	A[1] = 0;
	Eof = 0;
	while(!Eof)
	{
		free(A);
		A = read_str(prog, &Eof);
		filename = file_name(A);
		if (filename != 0)
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
					free(A);
					free(P);
					fclose(prog);
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
		//if (filename != 0)
			free(filename);
	}
	free(A);
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
