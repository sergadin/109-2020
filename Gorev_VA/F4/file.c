#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include "prog.h"

int main (int argc, const char **argv)
{
	if (argc != 3)
		return -1;
	dif(argv[1], argv[2]);
	return 0;
}
