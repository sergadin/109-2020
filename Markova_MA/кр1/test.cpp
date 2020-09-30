/*
#include "text.h"
#include <iostream>

int main()
{
	return 0;
}*/
#include "text.h"

int main(){
    queue n(3), b(2);
    cout << "Make Empty queue of 3 elements" << endl;
    cout << "reult of function print(): ";
    n.print();
    cout << "reult of function checkVoid(): ";
    if(n.checkVoid()) {
        cout << "empty" << endl;
    }
    n.push(1.5);
    n.push(3.0);
    n.push(5.2);
    cout << endl << "Add 3 elements to queue" << endl;
    n.print();
    cout << "reult of function checkfull(): ";
    if (n.checkfull()) {
        cout << "full" << endl;
    }
    cout << endl << "Resize and add 1 more elemets" << endl;
    n.resize(4);
    n.push(9.3);
    cout << "reult of function print(): ";
    n.print();
    cout << endl << "take 1 element from the queue" << endl;
    double k = n.pop();
    cout << "taken element: ";
    cout << k << endl;
    
    b.push(4.0);
    b.push(7.2);
    cout << "reult of function print(): ";
    n.print();
    cout << "Make other queue of 2 elements and add elemets" << endl;
    cout << "new queue: ";
    b.print();
    cout << "result of operation last queue + new queue:" << endl;
    queue c = n + b;
    c.print();
}