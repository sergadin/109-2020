#include <iostream>
#include "list.hpp"
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
    List <int> MyNumbers;
   
    cout << "список пуст? " << MyNumbers.is_empty() << endl;
    
    for (int i = 2; i < 10; i++)
     {
     // int z;
     // cout << ">> ";
     // cin >> z;
      MyNumbers.add_after(i);
      }
  //  MyNumbers.delete_first();
     MyNumbers.print();
   

    cout << "список пуст? " << MyNumbers.is_empty() << endl;

    cout << "В списке " << MyNumbers.elem_count() << " элементов" << endl;
    
  /*
    
      // Удаляем элементы, больше 5
    MyNumbers.go_first();
    do {
        if (MyNumbers.get_current() > 5 )
        MyNumbers.delete_this();
      else
        MyNumbers.go_next();
    } while (MyNumbers.get_current() != NULL);
    MyNumbers.print();
    
    
    
    MyNumbers.delete_list();
    MyNumbers.print();
    cout << "В списке " << MyNumbers.elem_count()<< " элементов" << endl; 
    */
    return 0;
};
