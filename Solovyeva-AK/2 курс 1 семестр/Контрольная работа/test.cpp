#include "IntSet.h"
/*
int main() {
    IntSet a(0, 5);
    a.add_elem(1);
    a.add_elem(4);
    a.add_elem(2);
    //a.print();
    IntSet b = a;
    //if(b == a) b.print();
    IntSet c(2, 4);
    c.add_elem(3);
    IntSet d = a * c;
    d.print();
    a.print();
    a*=c;
    a.print();   
    return 0;
}
*/
int main() {
    IntSet big(0, 100);
    const int max_iterations = 500;

    for(int iter = 0; iter < max_iterations; iter++) {
    IntSet temp(0, big.right());
    for(int item = temp.left(); item <= temp.right(); item++) {
        if((item % 7) > (iter % 11))
            temp.add_elem(item);
    }
    if(iter > 0)
        big = big * temp;
    else
        big = temp;
    }
    big = big;
    std::cout << "min = " << big.CheckMin() << ", max = " << big.CheckMax() << std::endl;
    
    
    try {
        IntSet invalid(-1, -2);
        cerr << "**** An exception was expected! *****" << endl;
        return -1;
    }
        catch(UserException& my) {
        cerr << "My error was detected!" << endl;
        cerr << "Code: " << my.code() << endl << "Message:" << my.message() << endl;
    }
  return 0;
}
