#include <iostream>
#include <cmath>

#include "dynarr.hpp"

using namespace std;

int main(void) {
	Array<double> list;

	try {
		list.pop();
	} catch (ListException& e) {
		cerr << e << endl;
	}

	list.push(5);
	cout << list << endl;
	list.push(6);
	cout << list << endl;
	list.unshift(78);
	cout << list << endl;
	list.shift();
	cout << list << endl;

	try {
		cout << list[6] << endl;
	} catch (ListException& e) {
		cerr << e << endl;
	}

	cout << list << endl;

	try {
		list.insert(10, 56);
	} catch (ListException& e) {
		cerr << e << endl;
	}
	
	Array<double> list2 = Array<double>(list);
	Array<double> list3;
	list3 = list2;
	cout << "Length: " << list.len() << endl;
	list[1] = 67;

	try {
		list[2] = 670; // Error
		cout << list[2] << endl;
	} catch (ListException& e) {
		cerr << e << endl;
	}

	for (double i = 1; i < 5e3; i *= 1.5) {
		list.push(i);
	}
	
	cout << "Length: " << list.len() << endl;
	cout << list << endl;

	return 0;
}
