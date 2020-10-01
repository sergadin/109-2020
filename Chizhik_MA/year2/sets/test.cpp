#include <iostream>
#include "sets.hpp"

using namespace std;

int main() {
  IntSet big(0, 100);
  const int max_iterations = 500;

  for(int iter = 0; iter < max_iterations; iter++) {
    IntSet temp(0, big.right());
    for(int item = temp.left(); item <= temp.right(); item++) {
      if((item % 7) > (iter % 11))
        temp.add_element(item);
    }
    if(iter > 0)
      big = big * temp;
    else
      big = temp;
  }
  big = big;
  std::cout << "min = " << big.min() << ", max = " << big.max() << std::endl;

  try {
    IntSet invalid(-1, -2);
    cerr << "**** An exception was expected! *****" << endl;
    return -1;
  }
  catch(IntSetException e) {
    printf("Oh no\n");
	return -1;
  }

  return 0;
}
