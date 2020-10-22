#include <iostream>
#include "kr3.h"

using namespace std;

int main() 
{
	
	try
	{   bonus person1(std::string("McDonald's"), 5);
		bonus person2(std::string("McDonald's"), 4);
        bonus person3(std::string("Shop"), 12);
        bonus person4(std::string("Shop"), 12);
        bonus person5(std::string("Shop"), 12);
		person1.dollars(4, 249.99);
		person2.dollars(2, 99.9999);
		samePerson(person1, person2);
		person3.dollars(6, 30399.99);
		person4.dollars(11, 4500);
        person4.dollars(11, 677.9);
		samePerson(person3, person4);
        person3==person4;
        person3==person5;
        person1==person2;
        std::cout<< person1 << endl;
        std::cout<< person2 << endl;
        std::cout<< person3 << endl;
        std::cout<< person4 << endl;
       
        return 0;
}
		
	catch(bonusError &err)
	{
		std::cout << "exseption  "<< err.get_reason() << std::endl;
	}
	return 0;
}
