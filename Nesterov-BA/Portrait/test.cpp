#include "profile.h"
#include <iostream>

using namespace std;

int main()
{
	try{
		profile s1("Sberbank", 5);
		profile s2("Sberbank", 5);
		profile a("Target", 10);
		const char* name;
		for(int i = 0; i<10; ++i){
			s1.transaction(2, 1000);
			s2.transaction(2, 50);
		}
		cout << s1.get_sum(2) <<endl;
		cout << s2.get_quantity(4) <<endl;
		s1.merge(s2);
		cout << s1.get_sum(2) <<endl;
		cout << s1.get_categories() <<endl;
		cout << s1.get_program() << endl;
		
}
	catch(Exception &exc)
	{
		std::cout << "EXCEPTION " << exc.message() << std::endl;
	}
	return 0;
}
