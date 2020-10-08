#include <iostream>
#include "class.h"
using namespace std;
//VectorClock(int dimension, int index)
int main() {


    try {
    VectorClock one(2, 1), two(2, 2);
    one.LocalEvent();
    one.print();
    two.EventMessage(one);
    two.print();
    one.print();
    } catch(UserException& my) {
        cerr << "my error is here" << endl;
        cerr << "code: " << my.code() << endl << "what happened: " << my.message() << endl;
    }
    return 0;
}
