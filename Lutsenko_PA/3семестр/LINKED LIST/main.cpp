
#include <iostream>
#include "list.hpp"

using namespace std;

int main()
{   typedef List<double> StudMarks;
   
    List<int> list_of_integers;
    List <IntList> list_of_list_of integers;
    
    List<int>::Iterator i = list_of_integers.begin();
    while (i.is_valid())
    {
        std::cout << i.get_current() << std::endl;
        i.go_next();
    }
};
