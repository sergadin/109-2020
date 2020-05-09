#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void INCLUDE(FILE *file, char *filename)
{
	char *A;
	char c;
	int i = 0;
	A = (char*)malloc(sizeof(char));
	A[0] = 0;
	fscanf(file, "%c", &c);
	while(!feof(file))
	{
		//printf("%c", c);
		A[strlen(A)] = c;
		A = (char*)realloc(A, (strlen(A) + 2) * sizeof(char));
		A[strlen(A)] = 0;
		fscanf(file, "%c", &c);
	}
//	file = fopen(filename, "w");
	while (i < strlen(A))
	{
		printf("%c", A[i]);
		i++;
	}	
	fclose(file);
//	fclose(file);
	free(A);
}

int main(void)
{
	FILE *file;
	FILE *programm;
	char *filename = "input.txt";
	char **A;
	if ((file = fopen(filename, "r")) == NULL)
	{
		printf("Íå óäàëîñü îòêðûòü ôàéë %s\n", filename);
		return -1;
	}
	
	INCLUDE(file, filename);
	
	return 0;
}
