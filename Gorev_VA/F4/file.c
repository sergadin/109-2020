#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>

int main (int argc, const char **argv)
{
	char *dir1;
	char *dir2;
	if (argc != 3)
		return -1;
	dir1 = (char*)malloc((strlen("dir1") + 1) * sizeof(char));
	strcpy(dir1, argv[1]);
	dir2 = (char*)malloc((strlen("dir2") + 1) * sizeof(char));
	strcpy(dir2, argv[2]);
	
	dif(dir1, dir2);

	free(dir1);
	free(dir2);
	return 0;
}
