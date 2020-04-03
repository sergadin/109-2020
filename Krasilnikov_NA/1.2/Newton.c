#include <stdio.h>
#include"Newton.h"

struct result calculation(double a, double b, double epsilon, RRFUN function)
{
  double length = (b - a);
  struct result answer;
  answer.iterations = 0;
  if ((*function)(a) * (*function)(b) > 0)
  {
    answer.rofc = 0;
    return answer;
  }
  while (length > epsilon)
  {
    length = length/2;
    if ((*function)(a) == 0)
    {
      answer.rofc = a;
      return answer;
    }
    if ((*function)(b) == 0)
    {
      answer.rofc = b;
      return answer;
    }
    a += length;
    if ((*function)(a) * (*function)(b) > 0)
    {
      a -= length;
      b -= length;
    }
    answer.iterations++;
  }
  answer.rofc = (a + b)/2;
  return answer;
}
