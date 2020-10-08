#include <string>
#include <iostream>
#include "clock.h"

int main(void)
{
    Clock C(2, 0);
    Clock CC(C);

    /*try
    {
        nextClock(nextClock(C), C);
    }
    catch (ClockError &err)
    {
        std::cout << "EXEPTION: " << err.get_reason() << "\n";
    }*/

    return 0;
}