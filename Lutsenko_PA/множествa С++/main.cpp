#include <iostream>
#include "IntSet.hpp"

using namespace std;

int main()
{
   IntSet q(0,10);
    q.put_item(1);
    q.put_item(2);
    q.put_item(3);
    q.put_item(4);
    IntSet q2(0,13);
    q2=q;
    IntSet q3(0,15);
    q3.put_item(1);
    q3.put_item(5);
    q3.put_item(7);
    q3.put_item(4);
    //if (q == q3)
    //{
      //  std::cout << "равны"<< std::endl;
    //}
   // q*=q3;
    q.delete_item(1)
   
    
    std::cout << "left = " << q.left() << ", right = " << q.right() << std::endl;
    std::cout << "min = " << q.min() << ", max = " << q.max() << std::endl;
    std::cout << "тут " << q.quantity() << "элементов" << std::endl;
    std::cout << "тут " << q2.quantity() << "элементов" << std::endl;
    cout << q << endl;
    
    
    
    return 0;
}
