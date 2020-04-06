#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"minimum.h"

double first(double x)
{
  return x * x * log(x);
}
int main ()
{
  struct otrezok answer;
  int epsilon = 0.01;
  answer = setka(first, epsilon, 0.2, 100);
  return 0;
}
