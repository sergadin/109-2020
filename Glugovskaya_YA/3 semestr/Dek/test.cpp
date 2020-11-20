#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Dek.h"

//using namespace std;

int main(){
	
	try{
		Deque <int> dek;
		Deque <double> dek2;
		Deque <int> dek3;
		dek.push_front(5);
		dek.push_front(24);
		dek.push_front(12);
		dek.push_front(56);
		dek.print();		
		dek2.push_front(0.000001);
		dek2.push_front(0.0002);
		dek2.push_front(00.2);
		dek2.push_front(000.1);
		dek2.print();
		dek3.push_front(121);
		dek3.push_front(122);
		dek3.push_front(123);
		dek3.push_front(125);
		dek3.push_front(128);
		dek3.print();
		//dek = dek3;

		/*dek.pop_front();
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
		dek.pop_front();*/
		dek.sort();
		cout << "--------Отсортировали---------" << endl;
		dek.print();
		Deque<int>::Iterator it = dek.begin();
		it.print(); 
		Deque<int>::Iterator it2 = dek.begin();
		it2.parametrs(13, 1);
		it.parametrs(10, 3);
		cout << "Before" << endl;
		it.print();
		it2.print();
		cout << "Middle" << endl;
		it = it2 + 2;
		it.print();
		it = it - 3;
		it.print();
		it++;
		it2 = dek.end();
		it.print();
		it2.print();
		dek.print();
		//dek.begin();
	//	it.start(dek);
	}
	
	catch (Error &err){
		std::cout << "EXC  "<< err.get_reason() << std::endl;
	}
	return 0;
}	 