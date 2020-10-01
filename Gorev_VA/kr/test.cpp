#include <iostream>
#include "intset.h"

int main(void)
{
	intset IS(-2, 2);
	std::cout << IS.is_empty() << "\n";
	IS.put(1);
	IS.put(1);
	IS.put(2);
	IS.put(2);
	IS.del(1);
	intset IS1(IS);
	std::cout << IS.is_empty() << "\n";
	return 0;
}