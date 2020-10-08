//
//  main.cpp
//  vectorclock
//
//  Created by Nastya Verkhovskaya on 08.10.2020.
//  Copyright © 2020 Nastya Verkhovskaya. All rights reserved.
//

#include <iostream>
#include "vectorclock.h"

int main() {
    VectorClock v = VectorClock(4, 3);
    v.update();
    v.print();
    VectorClock v1 = VectorClock(4, 2);
    v1.update();
    v1.get(v);
    v1.print();
    VectorClock v2 = VectorClock(4, 0);
    v2.update();
    v2.update();
    v2.print();
    
    std::cout << (v1 < v2) << "\n";
    
    std::cout << (v < v1) << "\n";
    
    
    return 0;
}

