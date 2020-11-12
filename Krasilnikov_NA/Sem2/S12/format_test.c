#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

int main(int argc, const char *argv[])
{
	FILE *fin, *fout;
	int ls; //los = Length_of_String
	if ((argc != 3) || (sscanf(argv[2], "%d", &ls) != 1))
	{
		printf("Usage %s [input file] [length of string]\n", argv[0]);
		return -1;
	}
	if ((fin = fopen(argv[1], "r")) == NULL)
	{
		printf("Invalid input file name\n");
		return -1;
	}
	if ((fout = fopen("output.txt", "w")) == NULL)
	{
		fclose(fin);
		return -1;
	}
	formatting(fin, fout, ls);
	return 0;
}
