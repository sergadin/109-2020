#include "iterator.h"
#include <iostream>

using namespace std;
int main()
{
	try{
	IntArray A(10);
	iterator_1 a = A.begin();
	iterator_1 b(3, &A);
		
			A.set_elem(1, 1);
			A.set_elem(2, 3);
			A.set_elem(3, 4);
			A.set_elem(4, 5);
			A.set_elem(5, 6);
			A.set_elem(6, 7);
			A.set_elem(7, 8);
			A.set_elem(8, 9);
			A.set_elem(9, 10);
			A.set_elem(10, 0);
		
	cout<< A << endl;
	cout << A.find_elem(2) << endl;
	A.del_elem(2); 
	cout<< A << endl;
	
	
	while (a.check_bound() == true)
	{
	
		cout << a.get_cmp() << endl;
		a.step();
		IntArray X = A;
		cout<< X << endl;	
		
	
	}
	
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
