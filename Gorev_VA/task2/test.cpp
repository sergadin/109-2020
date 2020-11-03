#include <iostream>
#include "list.h"

int main(void)
{
	list <int> L;
	L.add_item(1);
	L.add_item(2);
	std::cout << L.get_current_item() << "\n";
	std::cout << L.deletelist() << "\n";
	return 0;
}




























/*#include <string>
#include <iostream>
#include "clock.h"

int main(void)
{
    Clock C(2, 0);
    C = nextClock(C);

    for (int k = 0; k < 10; k++)
    {
        Clock temp = C;
        temp = C = temp;
        temp = temp;
        temp = C;
    }

    try
    {
        nextClock(nextClock(C), C);
    }
    catch (ClockError &err)
    {
        std::cout << "EXEPTION: " << err.get_reason() << "\n";
    }

    return 0;
}*/