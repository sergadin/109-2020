#include <stdio.h>
#include <stdlib.h>

#include "format.h"
#include "../libs/mystring/mystring.h"

int main(void)
{
  FILE *fin, *fout;
  if ((fin = fopen("input.txt", "r")) == NULL)
  {
    return -1;
  }
  if ((fout = fopen("output.txt", "w")) == NULL)
  {
    fclose(fin);
    return -1;
  }
  formatting(fin, fout);
  fclose(fin);
  fclose(fout);
  return 0;
}
