#include <iostream>
#include "list.hpp"
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
    List <int> MyNumbers;
    List <int> MyNumbers1;
    cout << "список пуст? " << MyNumbers.is_empty() << endl;
    
    for (int i = 2; i < 10; i++)
     {
      MyNumbers.construct(i);
      MyNumbers1.construct(i);
      }
   // if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
    MyNumbers = MyNumbers1;
    MyNumbers.print();
    MyNumbers.delete_first();
    MyNumbers.print();
    MyNumbers.add_first(1);
    MyNumbers.print(); 
    MyNumbers.set_current(7);
     MyNumbers.add_after(222);
    MyNumbers.print();
    MyNumbers.delete_this();
    MyNumbers.print();
    
   cout << "текузщтй " << MyNumbers.get_current() << endl;
    
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

  //  MyNumbers.delete_list();
   //cout << "список пуст? " << MyNumbers.is_empty() << endl;
   //cout << "В списке " << MyNumbers.elem_count()<< " элементов" << endl;
    
    return 0;
};
