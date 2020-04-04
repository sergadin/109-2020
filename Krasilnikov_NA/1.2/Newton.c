#include <stdio.h>
#include <math.h>
#include"Newton.h"

struct result calculation(double a, double b, double epsilon, RRFUN function, ErrorCode *error)
{
  double A, B, C;
  struct result answer;
  *error = CALC_OK;
  answer.iterations = 0;
  if ((*function)(a) * (*function)(b) > 0)
  {
    answer.rofc = 0;
    *error = CALC_NEOK;
    return answer;
  }
  if (fabs((*function)(a)) <= epsilon)
  {
    answer.rofc = a;
    return answer;
  }
  if (fabs((*function)(b)) <= epsilon)
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
  while ((fabs(((*function)(A))/(derivative(function, A, epsilon))) >= epsilon) && (answer. iterations < 100000000))
  {
    if (fabs((*function)(A)) <= epsilon)
    {
      answer.rofc = a;
      return answer;
    }
    if (fabs((*function)(B)) <= epsilon)
    {
      answer.rofc = b;
      return answer;
    }
    B = A - ((*function)(A))/(derivative(function, A, epsilon));
    C = A;
    A = B;
    B = C;
    answer.iterations++;
  }
  if (answer.iterations >= 99999999)
  {
    *error = CALC_NEOK;
  }
  answer.rofc = A;
  return answer;
}
double derivative(RRFUN function, double x, double h)
{
  return ((*function)(x + h) - (*function)(x))/(h);
}
double second_derivative(RRFUN function, double x, double h)
{
  return ((*function)(x + 2 * h) - 2 * (*function)(x + h) + (*function)(x))/(h * h);
}
