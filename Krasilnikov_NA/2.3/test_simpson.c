#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "simpson.h"
double first(double x);
int main()
{
  FILE *fin, *fout, *ans;
  int i, m, *answers;
  double a, b, epsion, result;
  RRFUN funcs[] = {first};
  m = 1;
  if ((fin = fopen("input.txt","r")) == NULL)
  {
      printf("INVALID INPUT FILE");
      return -1;
  }
  if ((ans = fopen("answers.txt","r")) == NULL)
  {
      printf("INVALID ANSWERS FILE");
      fclose(fin);
      return -1;
  }
  if ((fout = fopen("output.txt","w")) == NULL)
  {
      printf("INVALID OUTPUT FILE");
      fclose(ans);
      fclose(fin);
      return -1;
  }
  if ((answers = (int*) malloc(m * sizeof(int))) == NULL)
  {
      printf("MEMORY ALLOCATION ERROR");
      fclose(fin);
      fclose(ans);
      fclose(fout);
      free(array);
      return -1;
  }
  for(i = 0; i < m; i++)
  {
    if (fscanf(fin, "%lf", &answers[i]) != 1)
    {
      fclose(fin);
      fclose(ans);
      fclose(fout);
      free(array);
      return -1;
    }
  }
  if (fscanf(fin, "%lf", &epsilon) != 1)
  {
    fclose(fin);
    fclose(ans);
    fclose(fout);
    free(array);
    return -1;
  }
  if (fscanf(fin, "%lf %lf", &a, &b) != 2)
  {
    fclose(fin);
    fclose(ans);
    fclose(fout);
    free(array);
    return -1;
  }
  for(i = 0; i < m; i++)
  {
  result = integratea(a, b, epsilon, funcs[i]);
  if (result == answers[i])
      {
          fprintf(fout, "Test № %d: OK\n", (i + 1));
      }
      else
      {
          fprintf(fout, "Test № %d: LOSS\n", (i + 1));
          fclose(fin);
          fclose(ans);
          fclose(fout);
          free(array);
          free(answers);
          return -1;
      }
    }
fclose(fin);
fclose(ans);
fclose(fout);
free(array);
free(answers);
return 0;
}
double first(double x)
{
  return log(x + 2) * 3;
}
