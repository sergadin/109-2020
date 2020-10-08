#include "Lamport.h"
#include <iostream>

using namespace std;

int main()
{
	try{
		Lamport a(3,0);
		Lamport b(3,1);
		Lamport c(3,2);

		a.step();
		c.step();
		c.step();
		cout << a << b << c;
		cout << "a<c? " << (a<c) << endl;
		a.send(c);
		cout << a << b << c;
		cout << "a<c? "<< (a<c) << endl;
		c.send(a);
		cout << a << b << c;
		cout << "a<c? "<< (a<c) << endl;
		b = a;
		cout << a << b << c;
	}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
