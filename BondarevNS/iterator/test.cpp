#include "iterator.h"
#include <iostream>

using namespace std;
int main()
{
	try{
	IntArray A(10);
	iterator_1 a = A.begin();
	iterator_1 b(3, &A);
		for(int i = 1; i<11; i++)
		{
			A.set_elem(i, i);
		}
	cout<< A << endl;
	cout << A.find_elem(2) << endl;
	A.del_elem(2); 
	cout<< A << endl;
	while (a.check_bound() == true)
	{
		cout << a.get_cmp() << endl;
		a.step();
	}
	
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
