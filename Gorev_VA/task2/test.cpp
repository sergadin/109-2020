#include <iostream>
#include "list.h"

int main(void)
{
	int item = 1;
	list <int> *L = new list <int>(1);
	//deletelist(L);
	L->put_item(2);
	L->put_item(3);
	deletelist(L);

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