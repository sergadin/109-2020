#include <iostream>
#include "sets.hpp"

using namespace std;

int main() {
	try {
		IntSet big(0, 100);
		IntSet small(-100, -200);
	} catch(IntSetException& e) {
		cerr << e.message() << endl;
		return -1;
  	}
	return 0;
}
