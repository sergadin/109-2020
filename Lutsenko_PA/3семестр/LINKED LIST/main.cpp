#include <iostream>
#include "list.hpp"
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
    List <int> MyNumbers;
   
    MyNumbers.print();
    MyNumbers.add_first(1);
    for (int i = 2; i < 10; i++)
    {
      int z;
      cout << ">> ";
      cin >> z;
      MyNumbers.add_after(i);
        
    }
    MyNumbers.print();
    
    // Удаляем элементы, равные 0
    MyNumbers.go_first();
    do {
      if (MyNumbers.get_current() == 0)
        MyNumbers.delete_this();
      else
        MyNumbers.go_next();
    } while (MyNumbers.get_current() != NULL);
    MyNumbers.print();
    cout << "В списке " << MyNumbers.elem_count() << " элементов" << endl;
    
    
    MyNumbers.delete_list();
    MyNumbers.print();
    cout << "В списке " << MyNumbers.elem_count()<< " элементов" << endl;
    
    return 0;
};
