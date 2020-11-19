
#include <iostream>
#include "list.hpp"

using namespace std;

int main()
{
    typedef List <double> MyNumbers;
   
    MyNumbers.print();
    
    for (int i = 0; i < 10; i++)
    {
      double z;
      cout << ">> ";
      cin >> z;
      MyNumbers.add_after(z);
        
    }
    MyNumbers.print();
    
    // Удаляем элементы, равные 0
    ListItem *p = MyNumbers.getFirst();
    do {
      if (MyNumbers.getValue(p) == 0)
        p = MyNumbers.Delete(p);
      else
        p = MyNumbers.go_next();
    } while (p != NULL);
    MyNumbers.print();
    cout << "В списке " << MyNumbers.elem_count() << " элементов" << endl;
    
    
    list.delete_list();
    list.Print();
    cout << "В списке " << list.getCount() << " элементов" << endl;
    
    return 0;
};
