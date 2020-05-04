#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring.h"

int main(void)
{
	FILE *fin, *fout;
	if ((fin = fopen("input.txt", "r")) == NULL)
	{
		printf("Input file doesn't exist\n");
		return -1;
	}
	if ((fout = fopen("input.txt", "w")) == NULL)
	{
		printf("Output file doesn't exist\n");
		fclose(fin);
		return -1;
	}
	char *string = "kekekekek";
	string = (char*)malloc(4);
	string[0] = 'm';
	string[0] = 'a';
	string[0] = 'm';
	string[0] = '\0';
	char *kek;
	kek = (char*)malloc(3);
	kek[0] = 'p';
	kek[1] = 'a';
	kek[2] = '\0';
	kek = scopy(string, kek);	
	printf("\n\n%s\n\n", kek);
	free(string);
	free(kek);
	return 0;
}
