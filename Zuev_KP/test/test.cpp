#include <iostream>
#include "intset.h"

int main() 
{
  IntSet big(0, 100);
  const int max_itertions = 500;

  for(int iter = 0; iter < max_iterations; iter++) 
  {
    IntSet temp(0, big.right());
    for(int item = temp.left(); item <= temp.right(); item++) 
    {
      if((item % 7) > (iter % 11))
        temp.add(item);
    }
    if(iter > 0)
      big = big * temp;
    else
      big = temp;
  }
  big = big;
  std::cout << "min = " << big.min() << ", max = " << big.max() << std::endl;

  try 
  {
    IntSet invalid(-1, -2);
    std::cerr << "**** An exception was expected! *****" << endl;
    return -1;
  }
  catch(...) 
  {
    // ...
  }

  return 0;
}
