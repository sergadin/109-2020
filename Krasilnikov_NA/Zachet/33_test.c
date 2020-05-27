#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  FILE *fin, *fout;
  ErrorCode error;
  if ((fin = fopen("input.txt", "r")) == NULL)
  {
    printf("Some problems with input file.");
    return -1;
  }
  if ((fout = fopen("result.txt", "w")) == NULL)
  {
    printf("Some problems with result file.");
    fclose(fin);
    return -1;
  }
  matrix_transformation(fin, fout, &error);
  fclose(fin);
  fclose(fout);
  return 0;
}
