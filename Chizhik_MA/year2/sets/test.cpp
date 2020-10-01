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
	for (int i = A.left(); i < A.right(); i += 2) {
		A.add_element(i);
	}
	A = A;
	cout << "Minimum of A is " << A.min() << " and maximum of A is " << A.max() << endl;
	IntSet B(40, 100);
	for (int k = 40; k < B.right(); k += 3) {
		B.add_element(k);
	}
	IntSet C = A * B;
	cout << "C has " << C.len() << " elements" << endl;
	IntSet D(-200, 200);
	if (D.is_empty()) {
		cout << "D is empty" << endl;
	} else {
		cout << "D is not empty" << endl;
	}
	return 0;
}
