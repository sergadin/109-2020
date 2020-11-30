#include <iostream>
#include "list.hpp"
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
    List <double> MyNumbers;
    List <double> MyNumbers1;
    cout << "списки пусты? " << (MyNumbers.is_empty() & MyNumbers1.is_empty())<< endl;
    
    for (int i = 1; i < 10; i++)
     {
      MyNumbers.construct(i);
      MyNumbers1.construct(i);
      }
    
   cout << "M : "; MyNumbers.print();
   cout << "M1 : "; MyNumbers1.print();
    if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
       else cout << "M и M1 не равны" << endl;
    MyNumbers.delete_first();
    cout << "M : "; MyNumbers.print();
    MyNumbers.add_first(1);
    cout << "M : "; MyNumbers.print();
    MyNumbers.set_current(7);
    MyNumbers.add_after(222);
    cout << "M : ";  MyNumbers.print();
    MyNumbers.delete_this();
    if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
       else cout << "M и M1 не равны" << endl;
    

    
    cout << "M : ";  MyNumbers.print();
   MyNumbers = MyNumbers1;
   cout << "M : ";  MyNumbers.print();
 //  MyNumbers + MyNumbers1;
    

    cout << "В списке " << MyNumbers.elem_count() << " элементов.А теперь отсортируем в порядке убывания :" << endl;
     
    MyNumbers.sort();
    cout << "M : ";  MyNumbers.print();
    
    
 /*     // Удаляем элементы, больше 5
    MyNumbers.go_first();
    do {
        if (MyNumbers.get_current() < 5 )
        MyNumbers.delete_this();
      else
        MyNumbers.go_next();
    } while (!MyNumbers.is_empty());
    MyNumbers.print();
 */


       MyNumbers.delete_list();
  cout << "список M пуст? " << MyNumbers.is_empty() << endl;
   cout << "В списке " << MyNumbers.elem_count()<< " элементов" << endl;
    
    return 0;
};
