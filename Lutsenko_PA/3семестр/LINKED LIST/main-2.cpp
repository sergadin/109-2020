#include <iostream>
#include "list-2.hpp"

#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{  
   try 
   {
      List <double> MyNumbers;
      List <double> MyNumbers1;
      List <double> MyNumbers2;
    
      //cout << "списки пусты? " << (MyNumbers.is_empty() & MyNumbers1.is_empty())<< endl;
    
      for (int i = 1; i < 10; i++)
      {
         MyNumbers.add_item((float)i);
          MyNumbers1.add_item(i*3);
         MyNumbers2.add_item(i+1);
      }
       
    
      cout << "M : "; MyNumbers.print();
      cout << "M1 : "; MyNumbers1.print();
      if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
      else cout << "M и M1 не равны" << endl;
      MyNumbers.delete_first();
      cout << "M : "; MyNumbers.print();
      MyNumbers.add_first(1.0f);
      cout << "M : "; MyNumbers.print();
      MyNumbers.set_current(7);
      MyNumbers.add_item(22.0f);
      MyNumbers.add_item(33.0f);
      cout << "M : ";  MyNumbers.print();
      MyNumbers.delete_this();
      cout << "M : ";  MyNumbers.print();
      if (MyNumbers == MyNumbers1) cout << "M и M1 равны" << endl;
      else cout << "M и M1 не равны" << endl;
      MyNumbers = MyNumbers1;
      cout << "M : ";  MyNumbers.print();
 
  
      cout << "В списке " << MyNumbers.elem_count() << " элементов.А теперь отсортируем в порядке убывания :" << endl;
      MyNumbers.sort();
      cout << "M : ";  MyNumbers.print();
    
      cout << " А теперь сложим М2 и М:" << endl;
      cout << "M2 : "; MyNumbers2.print();
      cout << "M : ";  MyNumbers.print();
      (MyNumbers2+MyNumbers).print();
     
      
    
   
    
    
      //список списков
     
      cout << "список списков "<< endl;
      List < List <double> > My_List_Of_Lists;
      cout << " список из М , M1 и M2 пуст? " << My_List_Of_Lists.is_empty() << endl;
    
      My_List_Of_Lists.add_item(MyNumbers);
      My_List_Of_Lists.add_item(MyNumbers1);
      My_List_Of_Lists.add_item(MyNumbers2);
    
      cout << " а теперь список из М , M1 и M2 пуст? " << My_List_Of_Lists.is_empty() << endl;
    
     
      List < List <double> > My_List_Of_Lists2;
      My_List_Of_Lists2 =  My_List_Of_Lists;
    
      My_List_Of_Lists2.delete_first();

      cout << "количество элементов в списке из списков-1:" <<  My_List_Of_Lists.elem_count()  << endl;
      cout << "количество элементов в списке из списков-2:" <<  My_List_Of_Lists2.elem_count()  << endl;
      if (!( My_List_Of_Lists2 == My_List_Of_Lists)) cout << "Два списка из списков не равны" << endl;
    
    


    
      cout << "список м пуст? " << MyNumbers.is_empty() << endl;
      MyNumbers.delete_list();
      cout << "список м пуст? " << MyNumbers.is_empty() << endl;
     
        
      cout << "список м2 пуст? " << MyNumbers2.is_empty() << endl;
      MyNumbers2.delete_list();
      cout << "список м2 пуст? " << MyNumbers2.is_empty() << endl;
 
      cout << "список м1 пуст? " << MyNumbers1.is_empty() << endl;
      MyNumbers1.delete_list();
      cout << "список м1 пуст? " << MyNumbers1.is_empty() << endl;
   
      cout << "список из списков-1 пуст? " << MyNumbers2.is_empty() << endl;
    
      cout << "список из списков-1 пуст? " << MyNumbers2.is_empty() << endl;

      My_List_Of_Lists.delete_list();
      My_List_Of_Lists2.delete_list();
      
    
   }

   catch (Error &why)
   {
      std::cerr << "ERROR" << std::endl;
   }

   return 0;   
};
