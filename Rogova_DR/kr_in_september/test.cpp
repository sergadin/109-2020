#include <iostream>
#include "matr.h"

const int min_value = 1000000;

using namespace std;
int main()
{
	Matr q(min_value, min_value + 5);

	std::cout<< q<< endl;

	try
	{
		Matr q2(1, 7);
		q2.put(2);
		q = q2;
        q = q;
<<<<<<< HEAD
        q.add(min_value + 2);
=======
        q.put(min_value + 2);
>>>>>>> kak-to tak
		std::cout << "q: " << q << endl;
		std::cout << "q2: " << q2 << endl;
	}
	catch(MatrError &err)
	{
		std::cout << "EXC"<< err.get_reason() << std::endl;
	}
	try
        {
                Matr q3(1, 7);
		q3.put(2);
		Matr q1(2, 5);
		q1.put(2);
		q1.put(4);
		q = q1 * q3;
                std::cout << "q: " << q << endl;
                std::cout << "q2: " << q1 << endl;
        }
        catch(MatrError &err)
        {
                std::cout << "EXC"<< err.get_reason() << std::endl;
        }



	std::cout << q << endl;

	return 0;


}
