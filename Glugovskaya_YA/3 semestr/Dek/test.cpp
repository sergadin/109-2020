#include <iostream>
#include <stdio.h>
#include <cstring>

#include "Dek.h"

//using namespace std;

int main(){
	
	try{
		Deque <int> dek;
		dek.push_front(5);
		dek.push_front(10);
		dek.push_front(12);
		dek.print();
		dek.pop_front();
		dek.pop_front();
		dek.pop_front();
		dek.print();
		dek.push_back(89);
		dek.print();
		dek.pop_front();
		dek.print();
		dek.push_back(29);
		dek.push_back(89);
		dek.push_front(189);
		dek.pop_back();
		dek.print();
		dek.front();
		dek.back();
		dek.pop_front();
		dek.pop_front();
		dek.pop_front();
		
	}
	
	catch (Error &err){
		std::cout << "EXC  "<< err.get_reason() << std::endl;
	}
	return 0;
}	 