#include <iostream>
#include "node.h"

int main(void)
{
	int item = 1;
	node <int> *L = new node <int>(1);
	L->put_item(2);
	L->put_item(3);
	L->put_item(4);
	L->put_item(5);

	std::cout << L->get_item() << "\n";

	node <int> *N = new node <int>(0);
	*N = *L;
	std::cout << N->get_item() << "\n";
	deletenode(L);
	deletenode(N);
	deletenode(N);
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
