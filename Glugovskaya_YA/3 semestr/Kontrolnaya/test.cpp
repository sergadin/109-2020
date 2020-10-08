#include <iostream>
#include "Time.h"

using namespace std;

int main(){
	
	Time Proc0(3,0);
	
	try
	{
		Time Proc1(3, 1);
		Time Proc2(3, 2);
		Time Proc3(5, 2);
		Time Proc4(3, 2);
		Proc0.InEvent();
		Proc1.InEvent();
		Proc0.GetMessage(Proc1);
		if(Proc3 <= Proc0)
			std::cout<< 111111111111112<< endl;
		Proc3 = Proc0;
  		std::cout<< Proc3<< endl;
		std::cout<< Proc1<< endl;
  		return 0;
	}
	catch (TimeError &err){
		std::cout << "EXC  "<< err.get_reason() << std::endl;
	}
	std::cout << Proc0 << endl;
    return 0;
}