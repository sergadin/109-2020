#include <iostream>
#include "vector_clock.hpp"

using namespace std;

int main()
{
    vector_clock A(2, 0), B(2, 1);
    B.local_add(3);
    A.local_add();
    cout << A << endl;
    cout << B << endl;
    try
    {
        A.receve(B);
        cout << A << endl;
        cout << (A < B) << endl;
		A.local_add();
		cout << A << endl;
		cout << (A < B) << endl;
        
    }
	catch(vector_clock_Exception & err)
	{
		cout << err.message() << endl;
	}
	
	for(int i = 0; i < 1000000000000000; i++)
	{
		i -= 2;
	}
	
	
    return 0;
}
