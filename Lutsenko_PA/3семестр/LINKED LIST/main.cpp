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
    MyNumbers.set_current(9);
    MyNumbers.add_after(222);
    cout << "M : ";  MyNumbers.print();
    MyNumbers.delete_this();
    if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
       else cout << "M и M1 не равны" << endl;
    

    
    MyNumbers = MyNumbers1;
    cout << "M : ";  MyNumbers.print();

    cout << "В списке " << MyNumbers.elem_count() << " элементов.А теперь отсортируем в порядке убывания :" << endl;
    MyNumbers.sort();
    cout << "M : ";  MyNumbers.print();
    
    cout << " А теперь сложим М1 и М:" << endl;
    cout << "M1 : "; MyNumbers1.print();
    cout << "M : ";  MyNumbers.print();
    (MyNumbers1+MyNumbers).print();


    MyNumbers.delete_list();
    cout << "список M пуст? " << MyNumbers.is_empty() << endl;
  
    
    return 0;
};
