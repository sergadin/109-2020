#include <iostream>
#include "kuslin.h"

int main()
{
	ZZ a = 9, b = 1;
	for(int n=0; n < 4; n++)
		b = b * a;
	std::cout << "a^n = " << b << std::endl;
	if(a.isPositive())
		std::cout << "Это положительное число!" << std::endl;
} 
