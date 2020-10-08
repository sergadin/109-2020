//
//  vectorclock.cpp
//  vectorclock
//
//  Created by Nastya Verkhovskaya on 08.10.2020.
//  Copyright © 2020 Nastya Verkhovskaya. All rights reserved.
//

#include "vectorclock.h"
#include <iostream>
#include <stdexcept>
 

VectorClock::VectorClock(const int& n_, const int& k_) {
    if (k_ >= n_) {
        throw std::invalid_argument("k_ >= n_");
    }
    n = n_;
    v = new int[n_];
    for (int i = 0; i < n; ++i) {
        v[i] = 0;
    }
    k = k_;
}
 
VectorClock::~VectorClock() {
    delete v;
}
 
void VectorClock::update() {
    ++v[k];
}
 
void VectorClock::get(const VectorClock& other) {
    if (n != other.n) {
        throw std::invalid_argument("размерности не совпадают!");
    }
    for (int i = 0; i < n; ++i) {
        v[i] = std::max(v[i], other.v[i]);
    }
}
 
bool VectorClock::operator<(const VectorClock& other) const {
    if (n != other.n) {
        throw std::invalid_argument("размерности не совпадают!");
    }
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (v[i] < other.v[i]) {
            flag = true;
        }
        else if (v[i] > other.v[i]) {
                return false;
        }
    }
    return flag;
}
 
void VectorClock::print() {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << "\n";
}

