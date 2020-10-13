#include <iostream>
#include "clock.hpp"

using namespace std;

int main()
{
    VClock a(4,1);
    VClock b(4,2);
    VClock c(4,3);
    VClock d(5,4);
    
    
    a.Local();
    a.Local();
    a.Local();
    b.Local();
    b.Global(a);
    a.PrintCoordinates();
    b.PrintCoordinates();
    b == a;
   
    b.Local();
     b.Local();
    c.Global(b);
    b.PrintCoordinates();
    c.PrintCoordinates();
    c == b;
   // a == d;
   for (int k = 0; k < 10; k++)
    {
       VClock temp = a;
        VClock pain(17,-63);
        
        temp = temp;
        pain.Local();
    }
    
    
    
    return 0;
}
