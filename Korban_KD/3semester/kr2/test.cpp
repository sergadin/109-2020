#include <iostream>
#include "vector_clock.hpp"

using namespace std;

int main()
{
    vector_clock A(2, 0), B(2, 1);
    B.local_add(2);
    A.local_add();
    cout << A << endl;
    cout << A << endl;
    try
    {
        A.receve(B);
        cout << A << endl;
        cout << (A < B) << endl;
        
    }
	catch(vector_clock_Exception & err)
	{
		cout << err.message() << endl;
	}
    return 0;
}
