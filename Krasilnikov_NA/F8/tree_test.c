#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

#include "tree.h"

int main(int argc, const char *argv[])
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
  fclose(fout);
  return 0;
}
