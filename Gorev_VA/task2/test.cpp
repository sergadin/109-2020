#include <iostream>
#include "list.h"

int main(void)
{
	std::cout << "---Create \"list <int> L\"\n";
	list <int> L;
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Create \"list <int> M(L)\"\n";
	list <int> M(L);

	std::cout << "---Check operator ==: \"M == L\":\n";
	if (M == L)
		std::cout << "M = L\n\n";
	else
		std::cout << "M != L\n\n";

	std::cout << "---Find elements:\n";
	std::cout << "L:\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";

	std::cout << "\n";
	std::cout << "---Delete first element in L\n";
	L.del_item();
	std::cout << "---Find elements:\n";
	std::cout << "L:\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";

	std::cout << "\n";
	std::cout << "---Check operator ==: \"M == L\":\n";
	if (M == L)
		std::cout << "M = L\n";
	else
		std::cout << "M != L\n";
	std::cout << "---Check operator ==: \"L == L\":\n";
	if (L == L)
		std::cout << "L = L\n";
	else
		std::cout << "L != L\n";

	std::cout << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";

	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";


	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Check operator =: \"M = L\", \"L = L\", \"L = M\", \"M = L = M\"\n";
	M = L;
	L = L;
	L = M;
	M = L = M;

	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";

	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);

	list <int>::iterator i = L.begin();
	std::cout << "---Check class iterator: \"while i isnot last write current item\"\n";
	while (!i.is_last())
	{
		std::cout << i.get_current_item() << "\n";
		i.go_next();
	}
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";
	std::cout << "---Delete M\n";
	std::cout << "number of deleted elements in M: " << M.deletelist() << "\n";

	std::cout << "\n";
	std::cout << "---Add items 1, 2, 3 in L\n";
	L.add_item(1);
	L.add_item(2);
	L.add_item(3);
	std::cout << "---Check operator +: \"L + L\"\n";
	L + L;
	std::cout << "---Find elements:\n";
	std::cout << "L:\n";
	std::cout << "first element: " << L.get_first_item() << "\n";
	std::cout << "last element: " << L.get_last_item() << "\n";
	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";

	try
	{
		std::cout << "---Find elements:\n";
		std::cout << "L:\n";
		std::cout << "first element: " << L.get_first_item() << "\n";
		std::cout << "last element: " << L.get_last_item() << "\n";
	}
	catch (listError &err)
	{
		std::cout << "ECXEPTION: Error code: " << err.get_code() << "; Reason: " << err.get_reason() << "\n";
	}

	std::cout << "---Delete L\n";
	std::cout << "number of deleted elements in L: " << L.deletelist() << "\n";

	std::cout << "\n";
	std::cout << "---Check operator <<: \n";
	std::cout << "---L1 = (1);  L2 = (1, 2);  L3 = (1, 2, 3);  LL = (L1, L2, L3)\n";
	list <int> L1, L2, L3;
	L1.add_item(1);
	L3 = L2 = L1;
	L2.add_item(2);
	L3 = L2;
	L3.add_item(3);
	list < list <int> > LL;
	LL.add_item(L1);
	LL.add_item(L2);
	LL.add_item(L3);
	std::cout << "---LL: \n";
	std::cout << LL << "\n";
	return 0;
}