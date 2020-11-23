#include <math.h>
#include <iostream>
#include <cstdio>
#include <D_an.h>

int main()
{
	try
        {
	List<int> S;

	S.add_after(10);
	S.add_after(7);
	cout << "S"<< endl;
	S.Print();
	
	List<int> S1;
	S1.add_after(2);
	S1.add_after(3);
	cout << "S1"<< endl;
	S1.Print();
	
	List<int> S5;
	S5 = S;
	cout << "S5"<< endl;
	S5.Print();
	
	S.dell_all();
	cout << "S"<< endl;
	S.Print();

	List<int> L;
	cout << "L"<< endl;
	L.Print();
	}
	catch(ListExpaction &err)
        {
                std::cout << err.get_reason() << std::endl;
        }
	return 0;
}
