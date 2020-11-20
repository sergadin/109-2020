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
      MyNumbers.construct(i);
      }
    MyNumbers.print();
    MyNumbers.delete_first();
    MyNumbers.print();
    MyNumbers.add_first(1);
    MyNumbers.print(); 
    MyNumbers.set_current(7);
    MyNumbers.add_after(0);
    MyNumbers.print();
  //   cout << "текузщтй " << MyNumbers.get_current() << endl;
    cout << "список пуст? " << MyNumbers.is_empty() << endl;

    cout << "В списке " << MyNumbers.elem_count() << " элементов" << endl;
    
 /*     // Удаляем элементы, больше 5
    MyNumbers.go_first();
    do {
        if (MyNumbers.get_current() > 5 )
        MyNumbers.delete_this();
      else
        MyNumbers.go_next();
    } while (!MyNumbers.is_empty());
    MyNumbers.print();
   
*/

    MyNumbers.delete_list();
    cout << "список пуст? " << MyNumbers.is_empty() << endl;
    cout << "В списке " << MyNumbers.elem_count()<< " элементов" << endl; 
    
    return 0;
};
