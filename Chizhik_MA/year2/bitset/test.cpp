#include "bitset.hpp"
using namespace std;

int main() {
	//First test (incorrect range)
	try {
		BitIntSet small(-100, -200);
	} catch(BitIntSetException& e) {
		cerr << e << endl;
  	}

	//Second test (trying to get min/max of empty sets)
	try {
		BitIntSet emp(0, 4);
		cout << "Set emp = " << emp << ((emp.empty()) ? " (it is empty)" : "") << endl;
		emp.min();
	} catch(BitIntSetException& e) {
		cerr << e << endl;
	}
	try {
		BitIntSet emp2(-18, 12);
		emp2.add(8);
		emp2.add(-5);
		cout << "emp2 = " << emp2 << endl;
		emp2.clear();
		cout << "After clear() method emp2 = " << emp2 << endl;
		
		emp2.max();
	} catch(BitIntSetException& e) {
		cerr << e << endl;
	}

	//Third test (adding & min/max & left/right)
	BitIntSet Z(-200, 0);
	Z.add(-45);
	Z.add(656785);
	Z.add(-200);
	Z.add(0);
	Z.add(3);
	Z.add(-4789999);

	cout << "Z: " << Z << endl;
	for (int j = 0; j < 5; j++) {
		cout << j << (Z.belongs(j) ? " belongs" : " doesn't belong") << " to Z" << endl;
	}
	cout << "Minimum of Z is " << Z.min() << " and maximum is " << Z.max() << endl;
	cout << "Z's values belong to the segment [" << Z.left() << ", " << Z.right() << "]" << endl;

	//Fourth test (adding & removing & assigning to itself)
	BitIntSet A = BitIntSet(0, 50);
	for (int i = A.left(); i < A.right(); i += 2) {
		A.add(i);
	}
	cout << "A: " << A << endl;
	A = A;
	cout << "After assigning to itself" << endl;
	cout << "A: " << A  << endl;
	A.remove(48);
	
	cout << "A: " << A  << endl;
	cout << "A's values belong to the segment [" << A.left() << ", " << A.right() << "]" << endl;
	A.add(46); // Trying to add element that is already in the set; nothing happens
	A.remove(56); // Leads to showing warning message

	cout << "Minimum of A is " << A.min() << " and maximum of A is " << A.max() << endl;
	BitIntSet B(40, 100);
	for (int k = 40; k < B.right(); k += 3) {
		B.add(k);
	}

	//Fifth test (intersection)
	BitIntSet C = A * B;
	if (C <= C) {
		cout << "C is subset of C, that's great" << endl;
	}
	C *= C;
	C *= A * A;
	A = C;
	cout << "A now has " << A.len() << " element(s)" << endl;
	cout << "A: " << A << endl;

	//Seventh test
	BitIntSet X = BitIntSet(-200, 200);
	for (int a = 0; a < X.right(); a += 3) {
		X.add(a);
	}
	BitIntSet Y = BitIntSet(-100, 200);
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
