#include <iostream>
#include "sets.hpp"

using namespace std;

int main() {
	//First test
	try {
		IntSet small(-100, -200);
	} catch(IntSetException& e) {
		cerr << e.message() << endl;
  	}
	//Second test
	try {
		IntSet A(-200, 0);
		A.add_element(5);
	} catch(IntSetException& e) {
		cerr << e.message() << endl;
	}
	//Third test
	try {
		IntSet B(0, 4);
		B.min();
		B.max();
	} catch(IntSetException& e) {
		cerr << e.message() << endl;
	}
	//Fourth test
	IntSet A = IntSet(0, 50);
	for (int i = 0; i < 45; i += 2) {
		A.add_element(i);
	}
	A = A;
	cout << "Minimum of A is " << A.min() << " and maximum of A is " << A.max() << endl;
	return 0;
}
