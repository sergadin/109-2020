#include <iostream>
#include "intset.h"

using namespace std;

int main() 
{
  IntSet q(0, 100);
  q.put(5);
  q.put(10);
  q.put(15);
  q.put(50);
  q.put(55);
  std::cout << q << endl;
  cout << "left: "<< q.lima() << std::endl;
  cout << "right: "<< q.limb() << std::endl;
  cout << "max: "<< q.max() << std::endl;
  cout << "min: "<< q.min() << std::endl;
  q.exc(5);
  std::cout << q << endl;
  return 0;
}
