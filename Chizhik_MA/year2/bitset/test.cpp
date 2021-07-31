#include "bitset.hpp"
using namespace std;

int main(void) {
	// First test (incorrect range)
	try {
		BitIntSet small(-100, -200);
	} catch(BitIntSetException& e) {
		cerr << e << endl;
  	}

	// Second test (trying to get min/max of empty sets)
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

		try {
			cout << emp2[3] << endl;
		} catch(BitIntSetException& e) {
			cerr << e << endl;
		}

		cout << "emp2 = " << emp2 << endl;
		emp2.clear();
		cout << "After clear() method emp2 = " << emp2 << endl;

		emp2.max();
	} catch(BitIntSetException& e) {
		cerr << e << endl;
	}

	// Third test (adding & min/max & left/right & checking if element belongs to the set & cache)
	BitIntSet Z(-200, 0);
	Z.add(-45);
	Z.add(656785);
	Z.add(-200);
	Z.add(0);
	Z.add(3);
	Z.add(-4789999);
	cout << Z << endl;
	cout << "Printing last element using the operator[]..." << endl;
	cout << Z[Z.len() - 1] << endl;
	cout << "Adding -25" << endl;
	Z.add(-25);
	cout << Z << endl;

	cout << "\nZ: " << Z << endl;
	for (int j = 0; j < 5; j++) {
		cout << j << (Z.belongs(j) ? " belongs" : " doesn't belong") << " to Z" << endl;
	}
	cout << "Minimum of Z is " << Z.min() << " and maximum is " << Z.max() << endl;
	cout << "Z's values belong to the segment [" << Z.left() << ", " << Z.right() << "]\n" << endl;

	// Fourth test (adding & removing & assigning to itself)
	BitIntSet A = BitIntSet(0, 50);
	for (int i = A.left(); i < A.right(); i += 2) {
		A.add(i);
	}
	cout << "A: " << A << endl;
	A = A;
	cout << "After assigning to itself" << endl;
	cout << "A: " << A << endl;
	A.remove(48);

	cout << "A: " << A << endl;
	cout << "A's values belong to the segment [" << A.left() << ", " << A.right() << "]" << endl;
	A.add(46); // Trying to add element that is already in the set; nothing happens
	int status = A.remove(56);
	cout << "A.remove(56) returns " << status << endl;

	cout << "Minimum of A is " << A.min() << " and maximum of A is " << A.max() << "\n" << endl;
	BitIntSet B(40, 100);
	for (int k = 40; k < B.right(); k += 3) {
		B.add(k);
	}

	// Fifth test (equal sets, subtraction, one set is the subset of another)
	BitIntSet X = BitIntSet(-100, 50);
	const BitIntSet e(0, 0);
	cout << ((X == e) ? "X is empty" : "X is not equal to empty set, hmm...") << endl;

	for (int a = -25; a < X.right(); a += 5) {
		X.add(a);
	}
	BitIntSet Y = BitIntSet(-27, 100);
	for (int b = 45; b >= Y.left(); b -= 5) {
		Y.add(b);
	}
	if (X == Y) cout << "X = Y" << endl;

	cout << "Let's remove some elements from Y" << endl;
	Y.remove(0);
	Y.remove(35);
	Y.remove(-10);

	cout << "X: " << X << endl;
	cout << "Y: " << Y << endl;
	cout << "Length of Y is " << Y.len() << ", length of X is " << X.len() << endl;

	cout << "Y is" << (!(Y <= X) ? "n't" : "") << " the subset of X\n" << endl;

	cout << "Let's modify X" << endl;
	BitIntSet G(-40, 80);
	for (int k = -19; k < 76; k += 4) G.add(k);
	cout << "Set G = " << G << endl;
	cout << "Additional info (to get some cache): " << X[X.len() / 2] << " is in the middle of X" << endl;
	cout << G[G.len() / 2] << " is in the middle of G" << endl;
	X -= G;
	cout << "We subtract G from X" << endl;
	cout << "And now X = " << X << endl;

	if (!(Y <= X)) cout << "Y isn't the subset of X anymore\n" << endl;

	// Sixth test (intersection & set is a subset of itself & more cache)
	BitIntSet P = X * Y;
	cout << P[P.len() - 1] << " is the maximum of P" <<  endl;

	cout << "We now create copy of P and modify it" << endl;
	cout << endl;
	BitIntSet copy = P;
	copy.add(3);
	copy.add(-8);
	cout << endl;

	cout << "Length of X*Y is " << P.len() << ": " << P << endl;
	if (P <= P) {
		cout << "P is subset of P, that's great" << endl;
	}
	P *= P;
	cout << "A = " << A << endl;
	cout << "P = " << P << endl;

	P *= A * A;
	cout << "P = P * A = " << P << endl;
	A = P;

	cout << "A = P now has " << A.len() << " element(s)" << endl;
	cout << "A = " << A << "\n" << endl;

	// Seventh test (union)
	cout << "So, G = " << G << endl;
	cout << "And X = " << X << endl;
	cout << "Their union is " << (G + X) << "\n" << endl;

	// Eighth test (symmetrical difference)
	BitIntSet M(-100, 100), N(0, 200);
	for (int i = M.left(); i <= M.right(); i += 2) {
		M.add(i);
		N.add(i + 100);
	}

	cout << "M and N are the subsets of the set of even numbers" << endl;
	cout << "M is its intersection with the segment [-100, 100]" << endl;
	cout << "And N is its intersection with the segment [0, 200]" << endl;

	BitIntSet SD = M ^ N;

	// Ninth test (iterator)
	BitIntSet::iterator SD_Iterator = SD.start(SD.len() - 1, -1);
	BitIntSet::iterator SD_Iterator_copy = SD_Iterator;

	SD_Iterator.begin();
	SD_Iterator.next();
	SD_Iterator_copy = SD_Iterator_copy;

	for (cout << "M Δ Ν (reversed): {"; !SD_Iterator_copy.at_begin(); SD_Iterator_copy.next_step()) {
		cout << SD_Iterator_copy.curr() << ((SD_Iterator_copy.curr_index() > 0) ? ", " : "");
	}
	cout << "}" << endl;

	BitIntSet::iterator SD_Odd_Iterator = SD.start(1, 2);
	cout << "Now, we'll print every second element of M Δ N:" << endl;
	for (cout << "{"; !SD_Odd_Iterator.at_end(); SD_Odd_Iterator.next_step()) {
		cout << SD_Odd_Iterator.curr() << ((SD_Odd_Iterator.curr_index() < SD.len() - SD_Odd_Iterator.step()) ? ", " : "");
	}
	cout << "}" << endl;

	BitIntSet::iterator SD_Even_Iterator = SD.start(0, 2);
	cout << "Now, we'll print all elements of M Δ N with even indices:" << endl;
	for (cout << "{"; !SD_Even_Iterator.at_end(); SD_Even_Iterator.next_step()) {
		cout << SD_Even_Iterator.curr() << ((SD_Even_Iterator.curr_index() < SD.len() - SD_Even_Iterator.step()) ? ", " : "");
	}
	cout << "}" << endl;

	BitIntSet::iterator SD_E3 = SD.start(2, 3);
	for (cout << "Every third element: {"; !SD_E3.at_end(); SD_E3.next_step()) {
		cout << SD_E3.curr() << ((SD_E3.curr_index() < SD.len() - SD_E3.step()) ? ", " : "");
	}
	cout << "}" << endl;

	return 0;
}
