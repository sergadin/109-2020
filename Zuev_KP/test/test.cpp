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
  return 0;
}
