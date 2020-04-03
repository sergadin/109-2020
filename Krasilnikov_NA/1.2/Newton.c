#include <stdio.h>
#include <math.h>
#include"Newton.h"

struct result calculation(double a, double b, double epsilon, RRFUN function, ErrorCode *error);
{
  double A;
  struct result answer;
  *error = INT_OK;
  answer.iterations = 0;
  if ((*function)(a) * (*function)(b) > 0)
  {
    answer.rofc = 0;
    *error = CALC_NEOK;
  }
  if (fabs(*function)(a) <= epsilon)
  {
    answer.rofc = a;
    return answer;
  }
  if (fabs(*function)(b) <= epsilon)
  {
    answer.rofc = b;
    return answer;
  }
  if ((second_derivative(function, a, epsilon)) * (*function)(a) > 0)
  {
    A = a;
  }
  else
  {
    A = b;
  }


}
double derivative(RRFUN function, double x, double h)
{
  return ((*function)(x + h) - (*function)(x))/(h)
}
double second_derivative(RRFUN function, double x, double h)
{
  return ((*function)(x + 2 * h) - 2 * (*function)(x + h) + (*function)(x))/(h * h)
}
