#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"minimum.h"

struct otrezok
{
  double rightend;
  double leftend;
};


int main ()
{
  FILE *fin, *fout, *ans;
  int i, m;
  double a, b, epsilon, *answers;
  double answer;
  ErrorCode eofm; //error_of_minimslisation
  struct otrezok *otrezoks;
  RRFUN funcs[] = {first, second, third, fourth, fifth, sixth, seventh, eighth, nineth};
  m = 9;
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
  if ((answers = (double*) malloc(m * sizeof(double))) == NULL)
  {
    printf("MEMORY ALLOCATION ERROR");
    fclose(fin);
    fclose(ans);
    fclose(fout);
    return -1;
  }
  for(i = 0; i < m; i++)
  {
    if (fscanf(ans, "%lf", &answers[i]) != 1)
    {
      fclose(fin);
      fclose(ans);
      fclose(fout);
      free(answers);
      return -1;
    }
  }
  if (fscanf(fin, "%lf", &epsilon) != 1)
  {
    fclose(fin);
    fclose(ans);
    fclose(fout);
    free(answers);
    return -1;
  }
  if ((otrezoks = (struct otrezok*) malloc(m * sizeof(struct otrezok))) == NULL)
  {
    fclose(fin);
    fclose(ans);
    fclose(fout);
    free(answers);
    return -1;
  }

  for (i = 0; i < m; i++)
  {
    if (fscanf(fin, "%lf %lf", &otrezoks[i].leftend, &otrezoks[i].rightend) != 2)
    {
      fclose(fin);
      fclose(ans);
      fclose(fout);
      free(answers);
      free(otrezoks);
      return -1;
    }
  }
  for(i = 0; i < m; i++)
  {
    answer = integrate(otrezoks[i].leftend, otrezoks[i].rightend, epsilon, funcs[i], &eofi);
    fprintf(fout, "Test № %d: ", (i  + 1));
      if (eofi == MIN_NEOK)
      {
        fprintf(fout, "LOSS | Impossible to reach the defined accuracy\n");
        fclose(fin);
        fclose(ans);
        fclose(fout);
        free(answers);
        free(otrezoks);
        return -1;
      }
      if (fabs(answer - answers[i]) >= MAXOF3(answer, answers[i], 1) * epsilon)
      {
        fprintf(fout, "LOSS | Calculated value: %lf, Exact value: %lf, Error value: %lf\n", answer, answers[i], fabs(answer - answers[i]));
        fclose(fin);
        fclose(ans);
        fclose(fout);
        free(answers);
        free(otrezoks);
        return -1;
      }
      else
      {
        fprintf(fout, "OK | Calculated value: %lf, Exact value: %lf, Error value: %lf\n", answer, answers[i], fabs(answer - answers[i]));
      }
    }
  }
  fclose(fin);
  fclose(ans);
  fclose(fout);
  free(answers);
  free(otrezoks);
  return 0;
}

double first(double x)
{
  return x * x * log(x);
}
