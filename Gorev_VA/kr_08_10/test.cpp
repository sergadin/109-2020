#include "clock.h"

int main(void)
{
    clock C(2, 0);
    return 0;
}






















/*#include <iostream>
#include "intset.h"
#include <string>

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
        std::cout << "IS = IS1\n";
    else
        std::cout << "IS != IS1\n";
    if (IS == IS)
        std::cout << "IS = IS\n";
    else
        std::cout << "IS != IS\n";

    IS * IS1;
    std::cout << "min is " << (IS *= IS1).find_min() << "\n";
    std::cout << "left border is " << (IS *= IS1).left_bord() << "\n";

    try
    {
        intset I2(-2, 2);
        intset I3(I2);
    }
    catch (intsetError &err)
    {
        std::cout << "EXEPTION: " << err.get_reason() << "\n";
    }

    
	return 0;
}*/