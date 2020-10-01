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

    if (IS == IS1)
        std::cout << "IS = IS1";
    else
        std::cout << "IS != IS1";
    if (IS == IS)
        std::cout << "IS = IS";
    else
        std::cout << "IS != IS";

    std::cout << "min is " << (IS *= IS1).find_min() << "\n";
    std::cout << "left border is " << (IS *= IS1).left_bord() << "\n";
	return 0;
}