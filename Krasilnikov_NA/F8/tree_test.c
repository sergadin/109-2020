#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

#include "tree.h"

int main(int argc, char *argv[])
{
	FILE *fout; 
	if (argc != 3)
	{
		printf("Usage %s [directory] [output file]", argv[0]);
		return -1;
	}
	if ((fout = fopen(argv[2], "w")) == NULL)
	{
		printf ("Problems with output file.");
		return -1;
	}
	make_tree(argv[1], fout);
	fclose(fout);
	return 0;
}
