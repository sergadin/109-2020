#include <iostream>
#include "list.h"

int main(void)
{
	list <int> L;
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	list <int> M(L);
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";

	std::cout << "L:\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";

	L.del_item();
	std::cout << "\n";

	std::cout << "L:\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "first element: " << L.get_first_item() << "\n";

	std::cout << "\n";
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";

	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";

	std::cout << "\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";

	std::cout << "\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	M = L;
	L = L;
	M = M;

	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	return 0;
}