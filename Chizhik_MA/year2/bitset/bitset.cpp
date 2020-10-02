#include <iostream>
#include <string>

#include "bitset.hpp"

ostream& operator<< (ostream& os, const BitIntSetException& e) {
	os << "Error " << e.code() << ": " << e.message() << endl;
	return os;
}

//More methods to be written...
