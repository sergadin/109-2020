#include <iostream>
#include "list.h"

int main(void)
{
	list <int> L;
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	list <int> M;
	M.add_item(1);
	M.add_item(2);
	M.add_item(3);
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";

	std::cout << "L:\n";
	std::cout << "current element: " << L.get_current_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";

	L.del_item();
	std::cout << "\n";

	std::cout << "L:\n";
	std::cout << "current element: " << L.get_current_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";

	std::cout << "\n";
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";

	std::cout << "number of deleted elements: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements: " << M.deletelist() << "\n";
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