#include <iostream>
#include "clock.hpp"

using namespace std;

int main()
{
    VClock a(4,1);
    VClock b(4,2);
    VClock c(4,3);
    VClock d(5,4);
    
    a.PrintCoordinates();
    a.Local();
    a.Local();
    a.Local();
    b.Local();
    b.Global(a);
    a.PrintCoordinates();
    b.PrintCoordinates();
    a == b;
    a == c;
    b.Local();
     b.Local();
    c.Global(b);
    c.PrintCoordinates();
    c == b;
   // a == d;
    
    
    return 0;
}
