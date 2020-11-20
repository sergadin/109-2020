#include <iostream>
#include "Time.h"

using namespace std;

int main(){
	
	PortrPart Par0(std::string("Bank"), 2);
	
//	Time Proc0(3,0);
	
	try
	{
		PortrPart Par1(std::string("Bank"), 4);
		PortrPart Par6(std::string("Bank"), 4);
		PortrPart Par2(std::string("Pyaterocka"), 4);
		PortrPart Par3(std::string("Pyaterocka"), 8);
		PortrPart Par4(std::string("Lotorea"), 8);
		PortrPart Par5(std::string("Lotorea"), 8);
		Par1.SpendMoney(2, 30);
		Par1.SpendMoney(2, 50.5);
		Par2.SpendMoney(2, 50.5);
		Par4.SpendMoney(7, 80.5);
		Par5.SpendMoney(7, 60.5);
		
		Check(Par0, Par1);
		Check(Par4, Par5);
		std::cout<< Par1 << endl;
		std::cout<< Par2 << endl;
		Par1 <= Par6;
		Par4 <= Par5;
		Par1 = Par2;
		
  		std::cout<< Par1 << endl;
		std::cout<< Par2 << endl;
		std::cout<< Par3 << endl;
		std::cout<< Par4 << endl;
		std::cout<< Par5 << endl;
  		return 0;
	}
	catch (Error &err){
		std::cout << "EXC  "<< err.get_reason() << std::endl;
	}
	std::cout << Par0 << endl;
    return 0;
}