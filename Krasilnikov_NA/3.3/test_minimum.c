#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"minimum.h"

double first(double x)
{
  return x * x - 6 * x + 7;
}
int main ()
{
  struct otrezok answer;
  epsilon = 0.01;
  answer = setka(first, epsilon, -100, 100);
  printf ("%lf %lf", answer.leftend, answer.rightend);
  return 0;
}
