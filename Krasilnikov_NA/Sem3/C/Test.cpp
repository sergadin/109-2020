#include "List.h"

int main()
{
	try
	{
		List<int> S;

		S.push_back(10);
		S.push_back(7);
		cout << "S" << endl;
		S.print();
		cout << endl;

		List<string> S1;
		S1.push_back("Hello ");
		S1.push_back("world");
		cout << "S1" << endl;
		S1.print();
		cout << endl;

		List<int> S5;
		S5 = S;
		cout << "S5" << endl;
		S5.print();
		cout << endl;

		S.del_all();
		cout << "S" << endl;
		S.print();
		cout << endl;

		List<int> S4;
		S4.push_back(-12);
		S4.push_back(12);
		S4.push_back(56);
		S4 = S4 + S5;
		cout << "S4" << endl;
		S4.print();
		cout << endl;

		cout << "Third element in S4 is: " << S4.at(2);
	}
	catch (Exc& err)
	{
		cout << err.get_error() << endl;
	}
	return 0;
}