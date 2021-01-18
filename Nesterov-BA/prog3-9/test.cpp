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
	cout<< "This is A " << A << endl;
	a.check_bound();
	cout<< "This is A " << A << endl;
	/*for(int k=0; k<3; ++k){
		cout << "after check_bound "<< A.get_elem(3) << endl;
		//IntArray X=A;
		cout<< "This is A " << A << endl;
		//cout << "This is X " << X << endl;
		cout << "This is get_cmp " <<  a.get_cmp() << endl;
		cout << "after get_cmp " << A.get_elem(3) << endl;
		a.step();
		cout << "after step " << A.get_elem(3) << endl;
	}*/
	while (a.check_bound() == true)
	{
		cout << "after check_bound "<< A.get_elem(3) << endl;
		IntArray X=A;
		cout<< "This is A " << A << endl;
		cout << "This is X " << X << endl;
		cout << "This is get_cmp " <<  a.get_cmp() << endl;
		cout << "after get_cmp " << A.get_elem(3) << endl;
		a.step();
		cout << "after step " << A.get_elem(3) << endl;
	}
	
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
