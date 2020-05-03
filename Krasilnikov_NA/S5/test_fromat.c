#include <stdio.h>
#include <stdlib.h>

#include "format.h"

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
}
