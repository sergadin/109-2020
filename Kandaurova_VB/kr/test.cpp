#include <iostream>
#include "cl.h"
#include <string>
#include <cstdlib>

using namespace std;

int main() {
	cl a(3,0);
	try {
		cl c(3, 1);
		cl b(3, 2);
		a.send();
        a.send();
		c.send();
		a.receve(c);
        std::cout<< c<< endl;
		b = a;
  		std::cout<< b<< endl;
  		return 0;
	}
	catch(UserException &e) {
		std::cout << "exceptions: "<< e.get_reason() << std::endl;
    }
	std::cout << a << endl;
	return 0;
}
