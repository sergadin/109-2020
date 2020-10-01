
#include "text.h"
//#include <iostream>

int main()
{
	ZZ a(3,6), b(4,9);
	cout << "a, b"<< endl;
	a.print();
	//b.print();
	a.push_(5);
	a.print();
	if(b.isEmpty())
	{
		print("empty");
		cout << endl;
	}
	a.print();
	cout << a.size() << endl;
	a.clean_(5);
	a.print();
	
	return 0;
}
