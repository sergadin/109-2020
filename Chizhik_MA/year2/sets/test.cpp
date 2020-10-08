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
		A.add(5);
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
		A.add(i);
	}
	A = A;
	A.remove(48);
	try {
		A.add(46); //Trying to add element that is already in the set
		A.remove(56);
	} catch (IntSetException& e) {
		cerr << e.message() << endl;		
	}
	cout << "Minimum of A is " << A.min() << " and maximum of A is " << A.max() << endl;
	IntSet B(40, 100);
	for (int k = 40; k < B.right(); k += 3) {
		B.add(k);
	}

	//Fifth test (intersection)
	IntSet C = A * B;
	if (C <= C) {
		cout << "C is subset of C, that's great" << endl;
	}
	C *= C;
	C *= A * A;
	A = C;
	cout << "A now has " << A.len() << " element(s)" << endl;
	//Sixth test (emptiness)
	IntSet D(-200, 200);
	IntSet E = D;
	if (E.empty()) {
		cout << "E is empty" << endl;
	} else {
		cout << "E is not empty" << endl;
	}

	//Seventh test
	IntSet X = IntSet(-200, 200);
	for (int a = 0; a < X.right(); a += 3) {
		X.add(a);
	}
	IntSet Y = IntSet(-100, 200);
	for (int b = 198; b >= 0; b -= 3) {
		Y.add(b);
	}
	if (X == Y) cout << "X = Y" << endl;
	Y.remove(0);
	Y.remove(99);
	X.remove(3);
	cout << "Length of Y (modified) is " << Y.len() << ", length of X (also modified) is " << X.len() << endl;
	X *= Y;
	cout << "Length of X*Y is " << X.len() << endl;
	return 0;
}
