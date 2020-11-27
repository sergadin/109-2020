#include <cstdio>
#include <iostream>

using namespace std;

template<typename T>
struct list{
    list<T> *next;
    T data;
};
