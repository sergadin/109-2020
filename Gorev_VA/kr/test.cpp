#include <iostream>
#include "intset.h"

int main(void)
{
	intset IS(-2, 2), IS1(-2, 2);

	/*std::cout << IS.is_empty() << "\n";

    IS.put(0);
	IS.put(1);
	IS.put(1);
	IS.put(2);
	IS.put(2);

	IS.del(2);

	intset IS1(IS);

	std::cout << IS.is_empty() << "\n";*/

    IS.put(0);
    IS.put(0);
	IS.put(2);
	IS.put(2);

    IS1.put(1);
    IS1.put(1);
	IS1.put(2);
	IS1.put(2);

    intset IS2(-2, 2);
    IS2 = IS * IS1;

    std::cout << "min is " << IS2.find_min() << "\n";
    std::cout << "left border is " << IS2.left_bord() << "\n";
	return 0;
}