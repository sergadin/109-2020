#include <iostream>
#include "ZZ.h"

int main() {
  ZZ a = -7, b = 1;
  for(int n=0; n < 50; n++)
    b = b * a;
  std::cout << "a^50 = " << b << std::endl;
  if(a.isPositive())
    std::cout << "Это положительное число!" << std::endl;
} 
